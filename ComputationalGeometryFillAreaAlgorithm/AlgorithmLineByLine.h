#pragma once
#include<iostream>
#include<list>
#include <map>
#include"Polygon.h"
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

typedef int X;
typedef int Y;

struct RibData
{
	double y;
	double dx;
	double x;
	double y2;
	RibData(pair<Point2f, Point2f>& rib)
	{
		y = ceil(rib.first.y);
		dx = (rib.second.x - rib.first.x) / (rib.second.y - rib.first.y);
		x = rib.first.x + dx*(y - rib.first.y);
		y2 = rib.second.y;
		line = rib;
	}
	pair<Point, Point> line;
};

class AlgorithmLineByLine
{
public:
	

	//map<Y, list<X>> mapxls;
private:
	void haveSameY(int current_y, list<RibData>& wholeList, list<RibData>& toInsert )
	{
		for each (RibData item in wholeList)
		{
			if (item.y == current_y)
			{
				toInsert.push_back(item);
			}
		}
		toInsert.sort([](RibData first, RibData second)
		{
			return first.x < second.x;
		});
	}
	void paint_part(list<RibData>& data, Mat& mat, int y)//to implement
	{
		cout << y << endl;
		for (auto i = data.begin(); i != data.end(); ++i)
		{
			auto next = i;
			if (++next == data.end())
			{
				break;
			}
			cout <<'\t'<< i->x << " -> " << next->x << endl;

			//for(double j = i->x; j<next->x; ++j)
			line(mat, Point(i->x, y), Point(next->x, y), 100);
			if ((i->dx > 0 && next->dx < 0 || i->dx < 0 && next->dx>0)&& i->x==next->x)
			{
				cout << "Different signs " << endl;
			}
			++i;
		}
	}
	void local_x_sort(list<RibData>& data)
	{
		data.sort([&](RibData& first, RibData& second)
		{
			return first.x < second.x;
		});
	}

	list<RibData> _ribList;
public:
	AlgorithmLineByLine(vector<pair<Point2f, Point2f>> p);
	/*
	САР = пустой;
	y = y_список[ первый элемент ].y;
	do
	{
	САР.Добавить( ребра из y-списка, у которых
	ребро.y = y);
	// сохраняя упорядоченность САР по возрастанию x
	y_список.Удалить( ребра, у которых ребро.y = y );
	Закрасить промежутки ( x_2i - 1, x_2i ) в строке y;
	y++;
	foreach( ребро из САР по порядку )
	{
	if(y > ребро.y2)
	удалить ребро из САР;
	else
	{
	ребро.x += ребро.dx;
	while(соседнее_слева_ребро(ребро).x > ребро.x)
	поменять местами в САР ребро с соседним;}}}
	while(САР не пуст);
	*/
	
	/*void addToLists(Polygon& p)
	{
		for (size_t i = 0; i < p.line_segments.size(); i++)
		{
			auto y = ceil(p.line_segments[i].first.y);
			auto dx = (p.line_segments[i].second.x - p.line_segments[i].first.x) / (p.line_segments[i].second.y - p.line_segments[i].first.y);
			auto x = p.line_segments[i].first.x + dx*(y - p.line_segments[i].first.y);

			while (y <= p.line_segments[i].second.y)
			{
				auto current_list = mapxls[y];
				current_list.push_back(x);
				y++;
				x += dx;
			}
		}
	}*/



	void algorithm(Mat& mat)
	{
		_ribList.sort([&](RibData& first, RibData& second)
		{
			return first.y < second.y;
		});

		list<RibData> listOfActiveRibbs;
		auto y = _ribList.front().y;

		/*
		do
{
      САР.Добавить( ребра из y-списка, у которых
                                 ребро.y = y);
      // сохраняя упорядоченность САР по возрастанию x
      y_список.Удалить( ребра, у которых ребро.y = y );

      Закрасить промежутки ( x_2i - 1, x_2i ) в строке y;
      y++;

      foreach( ребро из САР по порядку )
      {
            if(y > ребро.y2)
                  удалить ребро из САР;
            else
            {
                  ребро.x += ребро.dx;
                  while(соседнее_слева_ребро(ребро).x > ребро.x)
                        поменять местами в САР ребро с соседним;
            }
      }
}
while(САР не пуст);*/
		do
		{
			//САР.Добавить(ребра из y - списка, у которых
			//	ребро.y = y);
			haveSameY(y, _ribList, listOfActiveRibbs);

			// сохраняя упорядоченность САР по возрастанию x
			//y_список.Удалить(ребра, у которых ребро.y = y);
			_ribList.remove_if([&](RibData elem)
			{
				return elem.y == y;
			});

			//Закрасить промежутки(x_2i - 1, x_2i) в строке y;
			//y++;
			paint_part(listOfActiveRibbs, mat, y);
			y++;

			/*foreach(ребро из САР по порядку)
			{
				if (y > ребро.y2)
					удалить ребро из САР;
				else
				{
					ребро.x += ребро.dx;
					while (соседнее_слева_ребро(ребро).x > ребро.x)
						поменять местами в САР ребро с соседним;
				}
			}*/
			for (auto i = listOfActiveRibbs.begin(); i != listOfActiveRibbs.end(); )
			{
				if (y >= (*i).y2)
				{
					auto val_to_remove = i;
					++i;
					listOfActiveRibbs.erase(val_to_remove);
				}
				else
				{
					i->x += i->dx;
					local_x_sort(listOfActiveRibbs);
					++i;
				}
			}
		} while (listOfActiveRibbs.size() != 0);
	};
	~AlgorithmLineByLine();
};


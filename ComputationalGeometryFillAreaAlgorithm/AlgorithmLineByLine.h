#pragma once
#include<iostream>
#include<list>
#include <map>
#include"Polygon.h"
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>

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
private:
	void insert_ribs_with_y_begin(double current_y, list<RibData>& wholeList, list<RibData>& toInsert )
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
	void paint_part(list<RibData>& data, Mat& mat, int y)
	{
		cout << y << endl;
		uchar* current_line = mat.ptr<uchar>(y);
		for (auto i = data.begin(); i != data.end(); ++i)
		{
			auto next = i;
			if (++next == data.end())
			{
				break;
			}

			cout <<'\t'<< i->x << " -> " << next->x << endl;


			if (i->x == next->x)
			{
				if (i->y < y && next->y2>y || i->y2<y && next->y>y)
				{
					continue;
				}
			}
			
			for (int j = i->x; j <= next->x; ++j)
			{
				current_line[j] = 100;
				Mat M;
				cv::resize(mat, M, Size(320, 320), 0, 0, cv::InterpolationFlags::INTER_NEAREST);
				imshow("", M  );
				waitKey();
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
	

	void algorithm(Mat& mat)
	{
		_ribList.sort([&](RibData& first, RibData& second)
		{
			return first.y < second.y;
		});

		list<RibData> listOfActiveRibbs;
		auto y = _ribList.front().y;


		do
		{
			//add to listOfActiveRibs ribs, which begin with current y
			insert_ribs_with_y_begin(y, _ribList, listOfActiveRibbs);

			// delete from _ribList ribs, which begin with current y
			_ribList.remove_if([&](RibData elem)
			{
				return elem.y == y;
			});

			//paint (x_2i - 1, x_2i) parts in y row
			paint_part(listOfActiveRibbs, mat, y);
			y++;
			// for each rib from listOfActiveRibs
			for (auto i = listOfActiveRibbs.begin(); i != listOfActiveRibbs.end(); )
			{
				//check if rib ends here
				if (y > i->y2)
				{
					auto val_to_remove = i;
					++i;
					listOfActiveRibbs.erase(val_to_remove);
				}
				else
				{
					//find value of next x
					i->x += i->dx;
					//sort listOfActiveRibs by x
					local_x_sort(listOfActiveRibbs);
					++i;
				}
			}

		} while (listOfActiveRibbs.size() != 0);
	};
	~AlgorithmLineByLine();
};


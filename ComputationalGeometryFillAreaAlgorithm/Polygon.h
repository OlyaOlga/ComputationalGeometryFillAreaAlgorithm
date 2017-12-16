#pragma once
#include <vector>
#include <opencv2\core.hpp>

using namespace std;
using namespace cv;

class Polygon
{
	vector<Point2f> points;
public:
	Polygon();
	vector<Point2f> get_points();
	vector<pair<Point2f, Point2f>> line_segments;
	void form_line_segments()
	{
		for (int i = 0; i < points.size()-1; ++i)
		{
			if (points[i].y < points[i + 1].y)
			{
				line_segments.push_back(make_pair(points[i], points[i+1]));
			}
			else
			{
				line_segments.push_back(make_pair(points[i+1], points[i]));
			}
		}
		if (points[points.size() - 1].y < points[0].y)
		{
			line_segments.push_back(make_pair(points[points.size() - 1], points[0]));
		}
		else
		{
			line_segments.push_back(make_pair(points[0], points[points.size() - 1]));
		}

	}
	friend istream& operator >> (istream& stream, Polygon& polygon);
	~Polygon();
};
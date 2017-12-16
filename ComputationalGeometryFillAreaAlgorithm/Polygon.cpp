#include "Polygon.h"



Polygon::Polygon()
{
}

vector<Point2f> Polygon::get_points()
{
	return points;
}


Polygon::~Polygon()
{
}

istream & operator >> (istream & stream, Polygon & polygon)
{
	while (!stream.eof())
	{
		int x;
		int y;
		stream >> x;
		stream >> y;
		polygon.points.push_back(Point(x, y));
	}
	return stream;
}

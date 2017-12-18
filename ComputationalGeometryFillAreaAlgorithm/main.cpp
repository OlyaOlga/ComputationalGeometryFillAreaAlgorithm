#include <iostream>
#include <opencv2\core.hpp>
#include <fstream>
#include "Raster.h"
#include "Polygon.h"
#include "AlgorithmLineByLine.h"

inline istream & operator >> (istream & stream, Mat & polygon)
{
	while (!stream.eof())
	{
		float x;
		float y;
		stream >> x;
		stream >> y;
		polygon.at<uchar>(Point2f(x, y)) = 255;
	}
	return stream;
}

Mat& operator<<(Mat& mat, Polygon& polygon)
{
	for (size_t i = 0; i < polygon.line_segments.size(); ++i)
	{
		line(mat, polygon.line_segments[i].first, polygon.line_segments[i].second, 255);
	}
	return mat;
}

void main()
{
	int size = 32;

	fstream file_inner_polygon("InnerPoints.txt");//"InnerPoints.txt"  test_inner
	fstream file_outer_polygon("OutterPoints.txt");//"OutterPoints.txt"  test

	Polygon innerPolygon;
	Polygon outerPolygon;
	file_inner_polygon >> innerPolygon;
	file_outer_polygon >> outerPolygon;

	innerPolygon.form_line_segments();
	outerPolygon.form_line_segments();

	Mat m = Mat::zeros(Size(32, 32), CV_8UC1);
	m << innerPolygon;
	m << outerPolygon;

	/*fstream file_all_points("my_total.txt");
	Polygon test_total;
	file_all_points >> test_total;
	test_total.form_line_segments();*/

	vector<pair<Point2f, Point2f>> all_line_segments;
	for (size_t i = 0; i < innerPolygon.line_segments.size(); i++)
	{
		all_line_segments.push_back(innerPolygon.line_segments[i]);
	}
	for (size_t j = 0; j < outerPolygon.line_segments.size(); j++)
	{
		all_line_segments.push_back(outerPolygon.line_segments[j]);
	}
	AlgorithmLineByLine alg(all_line_segments);
	alg.algorithm(m);

	//m << innerPolygon;
	//m << outerPolygon;
	Mat M;
	cv::resize(m, M, Size(320, 320), 0, 0, cv::InterpolationFlags::INTER_NEAREST);

	imshow("", M);
	waitKey();
}
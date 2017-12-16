#pragma once
#include <vector>
#include <opencv2\core.hpp>
# include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include<vector>
using namespace std;
using namespace cv;
class Raster
{
	Mat raster;
	int scale_coef;
public:
	Raster(int rows, int cols, int _scaleCoef=10);
	Mat get_raster();
	void print();
	void fill_cell(int i, int j);
	void print_vector_of_points(vector<Point>& points);
	~Raster();
};


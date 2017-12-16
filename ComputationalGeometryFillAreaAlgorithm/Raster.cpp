#include "Raster.h"

Raster::Raster(int rows, int cols, int _scale_coef)
{
	scale_coef = _scale_coef;
	raster = Mat(rows*scale_coef, cols*scale_coef, CV_8UC1);
	raster = 255;
}

Mat Raster::get_raster()
{
	return raster;
}

void Raster::print()
{
	imshow("Raster", raster);
}

void Raster::fill_cell(int row, int col)
{
	//--row;//counting rasters rows from 1
	//--col;//counting rasters columns from 1
	cv::rectangle(raster, Point(col*scale_coef, row*scale_coef), Point(col*scale_coef + scale_coef - 1, row*scale_coef + scale_coef - 1), 0, -1);
}

void Raster::print_vector_of_points(vector<Point>& points)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		fill_cell(points[i].y, points[i].x);
	}
}

Raster::~Raster()
{
}

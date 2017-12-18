#include "AlgorithmLineByLine.h"



AlgorithmLineByLine::AlgorithmLineByLine(vector<pair<Point2f,Point2f>> line_segments)
{
	for (int i = 0; i < line_segments.size(); ++i)
	{
		_ribList.push_back(RibData(make_pair(line_segments[i].first, line_segments[i].second)));
	}
}


AlgorithmLineByLine::~AlgorithmLineByLine()
{
}

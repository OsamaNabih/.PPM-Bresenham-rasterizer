#pragma once
#include <vector>
using namespace std;
class Bresenham
{
	int StartX;
	int StartY;
	int EndX;
	int EndY;
	int dx;
	int dy;
	int xStep;
	int yStep;
	float slope;
	void CalculateDeltas();
	void CalculateSteps();
public:
	Bresenham(int, int, int, int);
	void DrawLine(vector<vector<int>> &raster);
	~Bresenham();
};


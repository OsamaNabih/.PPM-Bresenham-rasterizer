#include "Bresenham.h"
#include <algorithm>
#include <vector>
using namespace std;

Bresenham::Bresenham(int startX, int startY, int endX, int endY)
{
	StartX = startX;
	StartY = startY;
	EndX = endX;
	EndY = endY;
	CalculateDeltas();
	CalculateSteps();
	if (dx == 0)
		slope = 1.1;
	else
		slope = (float(EndY - StartY)) / (EndX - StartX);
}


void Bresenham::DrawLine(vector<vector<int>> &raster)
{
	int P;
	int currX = StartX;
	int currY = StartY;

	if (abs(slope) > 1)
	{
		P = 2 * abs(dx) - abs(dy);
		raster[currY][currX] = 255;
		while (currY != EndY)
		{
			if (P < 0)
			{
				P += 2 * abs(dx);
			}
			else
			{
				P += 2 * abs(dx) - 2 * abs(dy);
				currX += xStep;
			}
			currY += yStep;
			raster[currY][currX] = 255;
		}
	}
	else
	{
		P = 2 * abs(dy) - abs(dx);
		raster[currY][currX] = 255;
		while (currX != EndX)
		{
			if (P < 0)
			{
				P += 2 * abs(dy);
			}
			else
			{
				P += 2 * abs(dy) - 2 * abs(dx);
				currY += yStep;
			}
			currX += xStep;
			raster[currY][currX] = 255;
		}
	}
	
}

void Bresenham::CalculateDeltas()
{
	dx = EndX - StartX;
	dy = EndY - StartY;
}

void Bresenham::CalculateSteps()
{
	if (dx < 0)
		xStep = -1;
	else if (dx > 0)
		xStep = 1;
	else
		xStep = 0;
	if (dy < 0)
		yStep = -1;
	else if (dy > 0)
		yStep = 1;
	else
		yStep = 0;
}

Bresenham::~Bresenham()
{
}

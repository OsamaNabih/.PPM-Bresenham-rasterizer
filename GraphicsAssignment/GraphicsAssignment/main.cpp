#include <iostream>
#include <fstream>
#include <sstream>
#include "Bresenham.h"
#include <math.h>
#include <vector>
using namespace std;

enum ParamIndexes {
	Xmin,
	Xmax,
	Ymin,
	Ymax,
	Xres,
	Yres,
	Filename
};

int main(int argc, char**argv)
{
	float params[10];
	string filename = "binaryclock.2d";
	
	int N = 6;
	if (argc == 7)
		N = argc - 1;
	else if (argc == 8)
	{
		N = 6;
		filename = argv[7];
	}
	else if (argc < 6)
	{
		cout << "Insufficient parameters";
		return 0;
	}
	for (int i = 0, j = 1; i < N; i++, j++)
	{
		string s = argv[j];
		istringstream point(s);
		if (!(point >> params[i]))
		{
			cout << "Conversion failure";
		}
	}
	vector<vector <int> > raster (params[Xres]);
	for (int i = 0; i < raster.size(); i++)
	{
		raster[i].resize(params[Yres], 0);
	}

	ifstream Poly(filename, ios::in);
if (Poly.is_open())
{
	string NewPoly;
	double X, Y;
	int pixelX1, pixelY1, pixelX2, pixelY2;
	pixelX2 = pixelY2 = 0;
	bool draw = false;
	while (getline(Poly, NewPoly))
	{
		//getline(Poly, NewPoly);
		if (NewPoly[0] == 'p' || NewPoly[0] == 'P' || NewPoly.size() == 0)
		{
			draw = false;
			continue;
		}
		else
		{
			stringstream point(NewPoly);
			point >> X;
			point >> Y;
			pixelX1 = pixelX2;
			pixelY1 = pixelY2;
			double num1 = X - params[Xmin];
			double denum = params[Xmax] - params[Xmin];
			double num2 = params[Xres] - 0.5;
			pixelX2 = floor(num1 * num2 / denum);
			num1 = Y - params[Ymin];
			denum = params[Ymax] - params[Ymin];
			num2 = params[Yres] - 0.5;
			pixelY2 = floor(num1 * num2 / denum);
			if (draw)
			{
				Bresenham NewLine(pixelX1, pixelY1, pixelX2, pixelY2);
				NewLine.DrawLine(raster);
			}
			draw = true;
		}
	}
	Poly.close();
}
else
{
	int x;
	cin >> x;
	cout << "Error: Could not open the file!" << endl;
	return 0;
}
ofstream out(filename + ".ppm", ios::out);
out << "P3\n";
out << params[Xres] << '\t' << params[Yres] << '\n';
out << 255 << '\n';


for (int i = 0; i < params[Xres]; i++)
{
	for (int j = 0; j < params[Yres]; j++)
	{
		cout << raster[i][j] << '\t';
		for (int k = 0; k < 3; k++)
		{
			//out << raster[i][j] << '\t';
			out << raster[params[Xres] - i - 1][j] << '\t';
		}
		out << endl;
	}
	cout << endl;
}

	cout << "\n\n";
	return 0;
}



//int main()
//{
//		vector<vector <int> > raster (1000);
//		for (int i = 0; i < raster.size(); i++)
//		{
//			raster[i].resize(1000, 0);
//		}
//	Bresenham Line(0, 0, 5, 5);
//	Line.DrawLine(raster);
//	return 0;
//}

//
//int main()
//{
//	float params[10];
//	string filename = "starbox.2d";
//
//	int N = 6;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> params[i];
//	}
//	
//	vector<vector <int> > raster(params[Xres]);
//	for (int i = 0; i < raster.size(); i++)
//	{
//		raster[i].resize(params[Yres], 0);
//	}
//
//	ifstream Poly(filename, ios::in);
//	if (Poly.is_open())
//	{
//		string NewPoly;
//		double X, Y;
//		int pixelX1, pixelY1, pixelX2, pixelY2;
//		pixelX2 = pixelY2 = 0;
//		int count = 0;
//		bool draw = false;
//		while (getline(Poly, NewPoly))
//		{
//			//getline(Poly, NewPoly);
//			if (NewPoly[0] == 'p' || NewPoly[0] == 'P' || NewPoly.size() == 0)
//			{
//				draw = false;
//				continue;
//			}
//			else
//			{
//				stringstream point(NewPoly);
//				point >> X;
//				point >> Y;
//				pixelX1 = pixelX2;
//				pixelY1 = pixelY2;
//				double num1 = X - params[Xmin];
//				double denum = params[Xmax] - params[Xmin];
//				double num2 = params[Xres] - 0.5;
//				pixelX2 = floor(num1 * num2 / denum);
//				num1 = Y - params[Ymin];
//				denum = params[Ymax] - params[Ymin];
//				num2 = params[Yres] - 0.5;
//				pixelY2 = floor (num1 * num2 / denum);
//				if (draw)
//				{
//					Bresenham NewLine(pixelX1, pixelY1, pixelX2, pixelY2);
//					NewLine.DrawLine(raster);
//				}
//				draw = true;
//			}
//		}
//		Poly.close();
//	}
//	else
//	{
//		int x;
//		cin >> x;
//		cout << "Error: Could not open the file!" << endl;
//		return 0;
//	}
//
//	
//	ofstream out(filename + ".ppm", ios::out);
//	out << "P3\n";
//	out << params[Xres] << '\t' << params[Yres] << '\n';
//	out << 255 << '\n';
//
//
//	for (int i = 0; i < params[Xres]; i++)
//	{
//		for (int j = 0; j < params[Yres]; j++)
//		{
//			cout << raster[i][j] << '\t';
//			for (int k = 0; k < 3; k++)
//			{
//				out << raster[i][j] << '\t';
//			}
//			out << endl;
//		}
//		cout << endl;
//	}
//
//	cout << "\n\n";
//
//	//for (int i = 0; i < N; i++)
//	//{
//	//	cout << params[i] << " ";
//	//}
//	//if (N >= 6)
//	//	cout << filename;
//
//	int x;
//	cin >> x;
//	return 0;
//}

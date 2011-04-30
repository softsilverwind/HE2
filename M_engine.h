#ifndef __M_ENGINE__
#define __M_ENGINE__

#include <cmath>
#include "structs.h"

namespace M_engine
{

class Random
{
	private:
		static bool isInit;
		static void initialize();

	public:
		static double randomd();
		static int randomsgn();
		static int randomi(int min, int max);
		static double randomdUp(double mul, double div);
		static double randomdDown(double mul, double div);
};

double angleOf(Coordinate2d start, Coordinate2d end);
double length(Coordinate2d start, Coordinate2d end);
Coordinate2d polarToXY(double radius, double angle);
}

#endif

#include <cstdlib>
#include <cmath>
#include <ctime>

#include "M_engine.h"

namespace M_engine
{

bool Random::isInit = false;

double Random::randomd()
{
	return ((double) rand()) / RAND_MAX;
}

int Random::randomsgn()
{
	return (rand() % 2 == 0) ? 1 : -1;
}

void Random::initialize()
{
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 5; ++i)
		rand();

	isInit = true;
}

int Random::randomi(int min, int max)
{
	if (!isInit)
		initialize();

	const int range = max - min + 1;

	return rand() % range + min;
}

double Random::randomdUp(double mul, double div)
{
	if (!isInit)
		initialize();
	
	return 1 - (mul * randomd() / div);
}

double Random::randomdDown(double mul, double div)
{
	if (!isInit)
		initialize();
	
	return (mul * randomd() / div);
}



double angleOf(Coordinate2d start, Coordinate2d end)
{
        if (end.x == start.x)
                if (end.y > start.y)
                        return M_PI / 2;
                else
                        return -M_PI / 2;
        else if (end.x >= start.x)
                return atan((end.y - start.y) / (end.x - start.x));
        else
                return atan((end.y - start.y) / (end.x - start.x)) + M_PI;
}

double length(Coordinate2d start, Coordinate2d end)
{
	return sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
}

Coordinate2d polarToXY(double radius, double angle)
{
	return Coordinate2d(radius*cos(angle), radius*sin(angle));
}

}



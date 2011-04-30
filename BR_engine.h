#ifndef __BR_ENGINE_H__
#define __BR_ENGINE_H__

#include <cmath>
#include "structs.h"

#ifndef M_PI
        /* 
	 * cmath in linux defines Mathematical PI, but this is not a
	 * standard, so Visual Studio does not.
	 */
        #define M_PI 3.14159 
#endif

#define POINTS 256
#define step (2 * M_PI / POINTS)


namespace BR_engine
{

class Circle
{
	private:
		static Coordinate2d vertex[POINTS];

	public:
		static void prepare();
		static void draw(Coordinate2d position, double radius, Color3d color);
};

class Line
{
	public:
		static void draw(Coordinate2d start, Coordinate2d end, Color3d color, unsigned int thickness = 1);
};

class Letter
{
};


void prepare();

}

#endif /* __BR_ENGINE_H__ */

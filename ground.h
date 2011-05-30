#ifndef __GROUND_H__
#define __GROUND_H__

#include <starlia.h>

#define GR_SIZE (257)
#define GR_2 (GR_SIZE / 2)

using namespace Starlia;

class Ground : public StarObject
{
	private:
		double points[GR_SIZE]; 	// the ground set points
		Color3d color;

	public:
		Ground(Color3d);
		double getYofX(double x);  	// returns Y of given X
		void draw(); 			// paints the ground, when initialised
		void indent(double x);		// intents the ground in x
		bool collides(Coordinate2d position);
};

#endif

#ifndef __GROUND_H__
#define __GROUND_H__

#include "structs.h"
#include "d_engine.h"

#define GR_SIZE (257)
#define GR_2 (GR_SIZE / 2)

namespace HE2
{

class Ground : public Drawable
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

}

#endif

#ifndef __DUD_H__
#define __DUD_H__

#include "structs.h"
#include "d_engine.h"

namespace HE2
{

class Dud : public Drawable
{
	private:
		Coordinate2d position;
		Coordinate2d velocity;
		double radius;
		Color3d color;

	public:
		Dud(Coordinate2d position, Coordinate2d velocity, double radius, Color3d color);
		Dud(Coordinate2d position, Coordinate2dPolar velocity, double radius, Color3d color);

		Coordinate2d getPosition();
		bool recalc();
		void draw();
};

}

#endif /* __DUD_H__ */

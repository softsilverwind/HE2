#ifndef __DUD_H__
#define __DUD_H__

#include <starlia.h>

using namespace Starlia;

class Dud : public StarObject
{
	private:
		Coordinate2d position;
		Coordinate2d velocity;
		double radius;
		Color3d color;

	public:
		Dud(Coordinate2d position, Coordinate2d velocity, double radius, Color3d color);

		Coordinate2d getPosition();
		bool recalc();
		void draw();
};

#endif /* __DUD_H__ */

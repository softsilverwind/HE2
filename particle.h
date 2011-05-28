#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <starlia.h>

using namespace Starlia;

class Particle
{
	private:
		//P_engine *parent;
		Coordinate2d position;
		Coordinate2d velocity;
		Coordinate2d acceleration;
		Color3d color;
		double life;
		Coordinate2d start;
		double hue;
	
	public:
		Particle(Coordinate2d position, Coordinate2d velocity, Coordinate2d acceleration, Color3d color, int life);

		bool recalc();
		void draw();
};

#endif /* __PARTICLE_H__ */

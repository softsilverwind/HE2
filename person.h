#ifndef __PERSON_H__
#define __PERSON_H__

#include "structs.h"
#include "ground.h"
#include "dud.h"
#include "d_engine.h"

namespace HE2
{

class Person : public Drawable
{
	private:
		typedef struct BodyPart
		{
			Coordinate2d start, end;
			Color3d color;
			BodyPart(Coordinate2d s, Coordinate2d e, Color3d c) : start(s), end(e), color(c) {};
		}
		BodyPart;

		Coordinate2d position;
		double radius;
		Color3d color;

		BodyPart body, rhand, lhand, rleg, lleg;
		BodyPart weapon, laser;

		double velocity, angle;

	public:
		Person(double x, Color3d color, Ground *ground);

		void pointWeapon(double x, double y);
		Dud *fire();
		void closeLaser();
		bool collides(Coordinate2d position);

		void draw();
};

}

#endif

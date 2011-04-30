#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include "dud.h"
#include "BR_engine.h"

#define acceleration (-10)

using namespace BR_engine;

namespace HE2
{

Dud::Dud(Coordinate2d position, Coordinate2d velocity, double radius, Color3d color)
	: position(position), velocity(velocity), radius(radius), color(color)
{
	TAG("dud");
}

Dud::Dud(Coordinate2d position, Coordinate2dPolar velocity, double radius, Color3d color)
	: position(position), radius(radius), color(color)
{
	TAG("dud");
	this->velocity.x = velocity.r * cos(velocity.a);
	this->velocity.y = velocity.r * sin(velocity.a);
}

Coordinate2d Dud::getPosition()
{
	return position;
}

bool Dud::recalc()
{
	position.x += velocity.x / 100;
	velocity.y += (double) acceleration / 100;
	position.y += velocity.y / 100;
	return true;
}

void Dud::draw()
{
	Circle::draw(position, radius, color);
}

}

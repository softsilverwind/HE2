#include <GL/gl.h>
#include <cmath>
#include <starlia.h>
#include "dud.h"
#include "globals.h"
#include "p_engine.h"

#define acceleration (-10)

using namespace Starlia;

Dud::Dud(Coordinate2d position, Coordinate2d velocity, double radius, Color3d color)
	: position(position), velocity(velocity), radius(radius), color(color)
{
}

Dud::Dud(Coordinate2d position, Coordinate2dpolar velocity, double radius, Color3d color)
	: position(position), radius(radius), color(color)
{
	this->velocity.x = velocity.r * cos(velocity.a);
	this->velocity.y = velocity.r * sin(velocity.a);
}

Coordinate2d Dud::getPosition()
{
	return position;
}

bool Dud::recalc()
{
	position.x += velocity.x / 10;
	velocity.y += (double) acceleration / 10;
	position.y += velocity.y / 10;

	if (position.x > SIZEX || position.x < 0) 
	{
		changePlayer();
		return false;
	}
	else if (ground->collides(position))
	{
		layer[1]->registerObject(new P_engine(Coordinate2d(position.x, ground->getYofX(position.x)),PARTICLES,TIME,SPEED,Color3d(1,0.3,0),P_engine::CHAMPAGNE), changePlayer);
		return false;
	}
	else if (player[0]->collides(position))
	{
		layer[1]->registerObject(new P_engine(position,PARTICLES,TIME,SPEED,Color3d(1,0,0),P_engine::CHAMPAGNE), reInit);
		++score[1];
		return false;
	}
	else if (player[1]->collides(position))
	{
		layer[1]->registerObject(new P_engine(position,PARTICLES,TIME,SPEED,Color3d(1,0,0),P_engine::CHAMPAGNE), reInit);
		++score[0];
		return false;
	}

	return true;
}

void Dud::draw()
{
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	glScaled(radius, radius, 1);
	Circle::draw(color);
	glPopMatrix();
}

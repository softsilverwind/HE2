#include <GL/glut.h>
#include <climits>
#include "globals.h"
#include "particle.h"
#include "p_engine.h"
#include "M_engine.h"

#define SIZE 2

using namespace M_engine;

namespace HE2
{

Particle::Particle(Coordinate2d position, Coordinate2d velocity, Coordinate2d acceleration, Color3d color, int life)
	: position(position), velocity(velocity), acceleration(acceleration), color(color), life(life), start(position)
{
	hue = Random::randomdUp(1,4);
}

bool Particle::recalc()
{
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	position.x += velocity.x;
	position.y += velocity.y;
	if (life != INT_MAX)
		--life;

	if (position.y < ground->getYofX(position.x))
		life = 0;

	return (life > 0);
}

void Particle::draw()
{
	glPushAttrib(GL_CURRENT_BIT);

	glColor3d(color.r * hue, color.g * hue, color.b * hue);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(position.x, position.y + SIZE);
	glVertex2d(position.x - SIZE, position.y);
	glVertex2d(position.x, position.y - SIZE);
	glVertex2d(position.x + SIZE, position.y);
	glEnd();

	glPopAttrib();
}

}

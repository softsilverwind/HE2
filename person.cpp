#include <GL/gl.h>
#include <starlia.h>
#include "ground.h"
#include "person.h"
#include "dud.h"

using namespace Starlia;

Person::Person(double x, Color3f color, Ground *ground)
	: position(x, ground->getYofX(x) + 20),
	radius(5),
	color(color),
	body(Coordinate2d(position.x, position.y - 5), Coordinate2d(position.x, position.y - 15), color),
	rhand(Coordinate2d(position.x, position.y - 5), Coordinate2d(position.x + 5, position.y - 10), color),
	lhand(Coordinate2d(position.x, position.y - 5), Coordinate2d(position.x - 5, position.y - 10), color),
	rleg(Coordinate2d(position.x, position.y - 15), Coordinate2d(position.x + 5, ground->getYofX(position.x + 5)), color),
	lleg(Coordinate2d(position.x, position.y - 15), Coordinate2d(position.x - 5, ground->getYofX(position.x - 5)), color),
	weapon(Coordinate2d(position.x, position.y - 10), Coordinate2d(position.x, position.y + 10), color),
	laser(Coordinate2d(position.x, position.y - 10), Coordinate2d(position.x, position.y - 10), Color3f(0,1,0))
{
}

void Person::draw()
{
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	glScaled(radius, radius, 1);
	Circle::draw(color);
	glPopMatrix();

	Line::draw(body.start, body.end, color);
	Line::draw(rhand.start, rhand.end, color);
	Line::draw(lhand.start, lhand.end, color);
	Line::draw(rleg.start, rleg.end, color);
	Line::draw(lleg.start, lleg.end, color);
	Line::draw(laser.start, laser.end, Color3f(0,1,0));
	Line::draw(weapon.start, weapon.end, color, 3);
}

void Person::pointWeapon(double x, double y)
{
	laser.end.x = x;
	laser.end.y = y;

	angle = angleOf(laser.start, laser.end);
	velocity = length(laser.start, laser.end);

	velocity /= 4.2;
	velocity = (velocity > 100) ? 100 : velocity;
	laser.end = polarToXY(velocity * 4.2, angle) + weapon.start;


	weapon.end = polarToXY(20, angle) + weapon.start;

	rhand.end = (weapon.end + weapon.start) / 2;
	lhand.end = weapon.end;
}

Dud *Person::fire()
{
	return new Dud(weapon.end, polarToXY(velocity, angle), 2, color);
}

void Person::closeLaser()
{
	laser.end = laser.start;
}

bool Person::collides(Coordinate2d pos)
{
	return (pos.y < position.y + 5 && pos.y > min(rleg.end.y, lleg.end.y) && pos.x < rleg.end.x + 5 && pos.x > lleg.end.x - 5);
}

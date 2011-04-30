#include <GL/glut.h>
#include "BR_engine.h"
#include "structs.h"

namespace BR_engine
{

Coordinate2d Circle::vertex[POINTS];

void Circle::prepare()
{
	for (int i = 0; i < POINTS / 8; i++)
	{
		vertex[i].x = cos(i * step);
		vertex[i].y = sin(i * step);

		vertex[POINTS/4 - i - 1].x = vertex[i].y;
		vertex[POINTS/4 - i - 1].y = vertex[i].x;

		/* Define POINTS in second quadrant */
		vertex[POINTS/4 + i].x = -vertex[i].y;
		vertex[POINTS/4 + i].y =  vertex[i].x;

		vertex[POINTS/2 - i - 1].x = -vertex[i].x;
		vertex[POINTS/2 - i - 1].y =  vertex[i].y;

		/* Define POINTS in third quadrant */
		vertex[POINTS/2 + i].x = -vertex[i].x;
		vertex[POINTS/2 + i].y = -vertex[i].y;

		vertex[(POINTS*3)/4 - i - 1].x = -vertex[i].y;
		vertex[(POINTS*3)/4 - i - 1].y = -vertex[i].x;

		/* Define POINTS in fourth quadrant */
		vertex[(POINTS*3)/4 + i].x =  vertex[i].y;
		vertex[(POINTS*3)/4 + i].y = -vertex[i].x;

		vertex[POINTS - i - 1].x =  vertex[i].x;
		vertex[POINTS - i - 1].y = -vertex[i].y;
	}

}

void Circle::draw(Coordinate2d position, double radius, Color3d color)
{
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3d(color.r, color.g, color.b);
	glTranslated(position.x, position.y, 0);

	glScaled(radius, radius, 0);

	glBegin(GL_POLYGON);

	for (int i = 0; i < POINTS; i++)
	{
		glVertex2f(vertex[i].x, vertex[i].y);
	}

	glEnd();

	glPopAttrib();
	glPopMatrix();
}

void Line::draw(Coordinate2d start, Coordinate2d end, Color3d color, unsigned int thickness)
{
	glPushAttrib(GL_CURRENT_BIT);

	glColor3d(color.r, color.g, color.b);
	glLineWidth(thickness);

	glBegin(GL_LINES);
	glVertex2d(start.x, start.y);
	glVertex2d(end.x, end.y);
	glEnd();

	glPopAttrib();
}

void prepare()
{
	Circle::prepare();
}

}

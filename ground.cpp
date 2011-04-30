#include <GL/glut.h>
#include "ground.h"
#include "M_engine.h"
#include "structs.h"

using namespace M_engine;

namespace HE2
{

Ground::Ground(Color3d color)
	: color(color)
{
	TAG("ground");
	points[GR_2] = 100;

	for (int i = 1; i <= GR_2; ++i)
	{
		points[GR_2 - i] = points[GR_2 - i + 1] + Random::randomi(-1,1);
		points[GR_2 + i] = points[GR_2 + i - 1] + Random::randomi(-1,1);
	}
}

double Ground::getYofX(double x)
{
	x *= ((double) GR_SIZE - 1) / SIZEX;
	int xint = (int) x;
	double y1 = points[xint];
	double y2 = points[xint + 1];

	return y1 + (x - xint) * (y2 - y1);
}

void Ground::draw()
{
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(color.r,color.g,color.b);

	glBegin(GL_POLYGON);

	glVertex2d(SIZEX, 0);
	for (int i = GR_SIZE - 1; i >= 0; --i)
	{
		glVertex2d(i * SIZEX / (GR_SIZE - 1), points[i]);
	}
	glVertex2d(0,0);

	glEnd();

	glPopAttrib();
}

void Ground::indent(double x)
{
	//todo
}

bool Ground::collides(Coordinate2d position)
{
	return position.y < getYofX(position.x);
}

}

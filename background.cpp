#include <GL/gl.h>
#include <starlia.h>
#include "globals.h"
#include "background.h"

Background::Background(Color3f colorh, Color3f colorl)
	: colorh(colorh), colorl(colorl)
{
}

void Background::draw()
{
	glClearColor(colorl.r, colorl.g, colorl.b, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);

	glColor3f(colorl.r, colorl.g, colorl.b);
	glVertex2d(0, SIZEY / 4);
	glVertex2d(SIZEX, SIZEY / 4);

	glColor3f(colorh.r, colorh.g, colorh.b);
	glVertex2d(SIZEX, SIZEY);
	glVertex2d(0, SIZEY);

	glEnd();
}

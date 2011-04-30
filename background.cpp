#include <GL/glut.h>
#include "structs.h"
#include "background.h"

namespace HE2
{

Background::Background(Color3d colorh, Color3d colorl)
	: colorh(colorh), colorl(colorl)
{

}

void Background::draw()
{
	glClearColor(colorl.r, colorl.g, colorl.b, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_POLYGON);

	glColor3d(colorl.r, colorl.g, colorl.b);
	glVertex2d(0, SIZEY / 4);
	glVertex2d(SIZEX, SIZEY / 4);

	glColor3d(colorh.r, colorh.g, colorh.b);
	glVertex2d(SIZEX, SIZEY);
	glVertex2d(0, SIZEY);

	glEnd();

	glPopAttrib();
}

}

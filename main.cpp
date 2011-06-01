#include <GL/glut.h>
#include <starlia.h>
#include <cstdio>
#include "structs.h"
#include "background.h"
#include "ground.h"
#include "person.h"
#include "dud.h"
#include "p_engine.h"
#include "globals.h"

using namespace Starlia;

typedef enum
{
	morning, noon, afternoon, rainy, night
}
timeOfDayType;

timeOfDayType timeOfDay;

Background *background;
unsigned int score[2];
unsigned int currPlayer;
Ground *ground;
StarLayer *layer[3];
Person *player[2];
bool firing;
int xscale,yscale;
bool iHasAKill = false;
Rain *rain;

unsigned int last_recalc;

void init();

void changePlayer()
{
	player[currPlayer]->closeLaser();
	currPlayer = (currPlayer + 1) % 2;
	firing = false;
}

void printScore()
{
	printf("Player1 : %u - Player2 : %u\n", score[0], score[1]);
}

void reInit()
{
	printScore();
	iHasAKill = false;

	layer[0]->unregisterObject(ground);
	layer[0]->unregisterObject(player[0]);
	layer[0]->unregisterObject(player[1]);
	if (rain)
		layer[1]->unregisterObject(rain);

	layer[2]->unregisterObject(background);

	init();
}

void resize(int width, int height)
{
	xscale = width;
	yscale = height;
	glViewport(0, 0, width, height);
}

void mouse(int x, int y)
{
	x *= ((double) SIZEX / xscale);
	y *= ((double) SIZEY / yscale);
	player[currPlayer]->pointWeapon(x,SIZEY - y);
	glutPostRedisplay();
}


void click(int button, int state, int x, int y)
{
	x *= ((double) SIZEX / xscale);
	y *= ((double) SIZEY / yscale);
	player[currPlayer]->pointWeapon(x,SIZEY - y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !firing)
	{
		layer[2]->registerObject(player[currPlayer]->fire());
		firing = true;
	}
}

void init()
{
	Color3d backUp, backDown, groundCol, personCol;

	timeOfDay = (timeOfDayType) randomi(0,4);
	rain = NULL;

	switch (timeOfDay)
	{
		case morning:
			backUp = Color3d(0, 0, randomdUp(1,4));
			backDown = Color3d(randomdUp(1,4) - 0.25, 0.25, 0.25);
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0,0,0);
			break;
		case noon:
			backDown = backUp = Color3d(0, 0, randomdUp(1,20));
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0,0,0);
			break;
		case afternoon:
			backUp = Color3d(0, 0, randomdUp(1,2));
			backDown = Color3d(randomdUp(1,4), 0.25, 0.25);
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0,0,0);
			break;
		case rainy:
			rain = new Rain(Coordinate2d(0, SIZEY), Coordinate2d(SIZEX, 0), 100, 5, true);
			layer[1]->registerObject(rain);
			/* nobreak */
		case night:
			backDown = backUp = Color3d(0, 0, randomdDown(1,4));
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0.5,0.5,0.5);
			break;
		default:
			fputs("We should not have come here, heh", stderr);
			exit(1);
	}
	background = new Background(backUp, backDown);
	ground = new Ground(groundCol);
	player[0] = new Person(randomi(25,75),personCol,ground);
	player[1] = new Person(randomi(725,775),personCol,ground);
	layer[2]->registerObject(background);
	layer[0]->registerObject(ground);
	layer[0]->registerObject(player[0]);
	layer[0]->registerObject(player[1]);
	currPlayer = randomi(0,1);
	firing = false;
}

void glmain(int argc, char** argv)
{
}

int main(int argc, char** argv)
{
	puts("HE Training grounds not yet 0.5 (not yet 1.00 beta1) codename \"You can't yet reach the stars\"");
	puts("THIS IS STARLIAAAAAAAAAAAAA!");
	puts("THIS IS SEGFAUUUUUUUUUUUULT!");

	layer[0] = new StarLayer(Coordinate2d(800, 600));
	layer[1] = new StarLayer(Coordinate2d(800, 600));
	layer[2] = new StarLayer(Coordinate2d(800, 600));
	StarCore::registerLayerBackground(layer[0]);
	StarCore::registerLayerBackground(layer[1]);
	StarCore::registerLayerBackground(layer[2]);
	init();

	StarCore::init("HE Training Grounds 2 not yet v1.00-beta1", SIZEX, SIZEY);

	glutPassiveMotionFunc(mouse);
	glutMotionFunc(mouse);
	glutMouseFunc(click);
	glutReshapeFunc(resize);

	StarCore::loop();

	return 0;
}

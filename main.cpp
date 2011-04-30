#include <GL/glut.h>
#include <cstdio>
#include "structs.h"
#include "background.h"
#include "ground.h"
#include "person.h"
#include "dud.h"
#include "M_engine.h"
#include "p_engine.h"
#include "d_engine.h"
#include "BR_engine.h"

#define PARTICLES 500
#define TIME 1000
#define SPEED 0.5

using namespace M_engine;

namespace HE2
{

timeOfDayType timeOfDay;

Background *background;
Ground *ground;
Person *player[2];
unsigned int score[2];
unsigned int currPlayer;
bool firing;
Dud *dud = NULL;
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

	D_engine::unregisterFull(rain);
	D_engine::unregisterDrawOnly(background);
	D_engine::unregisterDrawOnly(ground);
	D_engine::unregisterDrawOnly(player[0]);
	D_engine::unregisterDrawOnly(player[1]);

	init();
}

void display()
{
	D_engine::draw();
	glutSwapBuffers();
}

void mouse(int x, int y)
{
	x *= ((double) SIZEX / xscale);
	y *= ((double) SIZEY / yscale);
	player[currPlayer]->pointWeapon(x,SIZEY - y);
	glutPostRedisplay();
}

void resize(int width, int height)
{
	xscale = width;
	yscale = height;
	glViewport(0, 0, width, height);
}

void idle(int _)
{
	D_engine::recalc();

	if (dud)
	{
		Coordinate2d dudpos = dud->getPosition();

		if (dudpos.x > SIZEX || dudpos.x < 0) 
		{
			D_engine::unregisterFull(dud);
			dud = NULL;
			changePlayer();
		}
		else if (ground->collides(dudpos))
		{
			D_engine::unregisterFull(dud);
			dud = NULL;
			D_engine::registerFull(new P_engine(Coordinate2d(dudpos.x, ground->getYofX(dudpos.x)),PARTICLES,TIME,SPEED,Color3d(1,0.3,0),P_engine::CHAMPAGNE), changePlayer, true, true);
		}
		else if (player[0]->collides(dudpos))
		{
			D_engine::unregisterFull(dud);
			dud = NULL;
			D_engine::registerFull(new P_engine(dudpos,PARTICLES,TIME,SPEED,Color3d(1,0,0),P_engine::CHAMPAGNE), reInit, true, true);
			++score[1];
		}
		else if (player[1]->collides(dudpos))
		{
			D_engine::unregisterFull(dud);
			dud = NULL;
			D_engine::registerFull(new P_engine(dudpos,PARTICLES,TIME,SPEED,Color3d(1,0,0),P_engine::CHAMPAGNE), reInit, true, true);
			++score[0];
		}
	}

	glutTimerFunc(1, idle, 42);
	glutPostRedisplay();
}


void click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !firing)
	{
		dud = player[currPlayer]->fire();
		D_engine::registerFull(dud, NULL, false, false);
		firing = true;
	}
}

void init()
{
	Color3d backUp, backDown, groundCol, personCol;

	BR_engine::prepare();
	timeOfDay = (timeOfDayType) Random::randomi(0,4);

	switch (timeOfDay)
	{
		case morning:
			backUp = Color3d(0, 0, Random::randomdUp(1,4));
			backDown = Color3d(Random::randomdUp(1,4) - 0.25, 0.25, 0.25);
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0,0,0);
			break;
		case noon:
			backDown = backUp = Color3d(0, 0, Random::randomdUp(1,20));
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0,0,0);
			break;
		case afternoon:
			backUp = Color3d(0, 0, Random::randomdUp(1,2));
			backDown = Color3d(Random::randomdUp(1,4), 0.25, 0.25);
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0,0,0);
			break;
		case rainy:
			rain = new Rain(Coordinate2d(0, SIZEY), Coordinate2d(SIZEX, 0), 100, 0.5, true);
			D_engine::registerFull(rain, NULL, false, false);
			/* nobreak */
		case night:
			backDown = backUp = Color3d(0, 0, Random::randomdDown(1,4));
			groundCol = Color3d(1,0.6,0.4);
			personCol = Color3d(0.5,0.5,0.5);
			break;
		default:
			fputs("We should not have come here, heh", stderr);
			exit(1);
	}
	background = new Background(backUp, backDown);
	ground = new Ground(groundCol);
	player[0] = new Person(Random::randomi(25,75),personCol,ground);
	player[1] = new Person(Random::randomi(725,775),personCol,ground);
	D_engine::registerDrawOnly(background);
	D_engine::registerDrawOnly(ground);
	D_engine::registerDrawOnly(player[0]);
	D_engine::registerDrawOnly(player[1]);
	currPlayer = Random::randomi(0,1);
	firing = false;
}

void glmain(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(SIZEX,SIZEY);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

	glutCreateWindow("HE Training Grounds 2 v1.00-alpha5");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,SIZEX,0,SIZEY);

	glutDisplayFunc(display);
	glutPassiveMotionFunc(mouse);
	glutMotionFunc(mouse);
	glutReshapeFunc(resize);
	glutMouseFunc(click);
	glutTimerFunc(1, idle, 42);
	glutMainLoop();
}

}

using namespace HE2;
int main(int argc, char** argv)
{
	puts("HE Training grounds 0.45 (1.00 alpha5) codename \"Re-F*ck-Tor\"");
	puts("Warning, everything is expected to break in 0.45");
	puts("Values of β will give rise to dom!");
	init();
	glmain(argc, argv);
	return 0;
}

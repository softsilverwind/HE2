#include <list>
#include <cmath>
#include <climits>
#include <GL/glut.h>
#include <starlia.h>
#include "p_engine.h"
#include "particle.h"
#include "structs.h"
#include "globals.h"

using namespace Starlia;

using namespace std;

P_engine::P_engine(Coordinate2d position, int number, int time, double maxvel, Color3d color, Effect effect)
	: position(position)
{
	double tempvel, tempangle;

	if (effect == CHAMPAGNE)
	{
		for (int i = 0; i < number; ++i)
		{
			tempvel = randomd() * maxvel;
			tempangle = randomd() * M_PI / 7 + 3 * M_PI / 7;
			Particle temp(position, Coordinate2d(randomsgn() * tempvel * cos(tempangle), tempvel * sin(tempangle)), Coordinate2d(0,-0.05), color, randomi(time/4,time));
			particleList.push_back(temp);
		}
	}
	else
	{
		for (int i = 0; i < number; ++i)
		{
			tempvel = randomd() * maxvel;
			tempangle = randomd() * 2 * M_PI;
			Particle temp(position, Coordinate2d(randomsgn() * tempvel * cos(tempangle), randomsgn() * tempvel * sin(tempangle)), Coordinate2d(0,0), color, randomi(time/4,time));
			particleList.push_back(temp);
		}
	}
}

bool P_engine::recalc()
{
	for (list<Particle>::iterator it = particleList.begin(); 
			it != particleList.end(); ++it)
	{
		if (!it->recalc())
			particleList.erase(it--);
	
	}

	return (!particleList.empty());
}

void P_engine::draw()
{
	for (list<Particle>::iterator it = particleList.begin(); 
			it != particleList.end(); ++it)
		it->draw();
}

Rain::Rain(Coordinate2d topleft, Coordinate2d botright, int number, double velocity, bool thunder)
	: topleft(topleft), botright(botright), velocity(velocity), thunder(thunder)
{
	int i;

	for (i = 0; i < number; ++i)
	{
		Coordinate2d position(randomi(topleft.x, botright.x), randomi(topleft.y, topleft.y + (topleft.y - botright.y)));
		Particle temp(position, Coordinate2d(0, -velocity), Coordinate2d(0,0), Color3d(0,0,1), INT_MAX);
		particleList.push_back(temp);
	}

	nextThunder = randomi(50,500);
}

bool Rain::recalc()
{
	for (vector<Particle>::iterator it = particleList.begin(); 
			it != particleList.end(); ++it)
	{
		if (!it->recalc())
		{
			Coordinate2d position(randomi(topleft.x, botright.x), SIZEY);
			*it = Particle(position, Coordinate2d(0, -velocity), Coordinate2d(0,0), Color3d(0,0,1), INT_MAX);
		}
	}

	if (thunder)
		--nextThunder;

	if (!nextThunder)
	{
		nextThunder = randomi(50,500);
		layer[1]->registerObject(new Thunder(Coordinate2d(randomi(0,SIZEX), SIZEY), Coordinate2d(SIZEX/10, SIZEY/3), randomi(50,100)));
	}

	return true;
}

void Rain::draw()
{
	for (vector<Particle>::iterator it = particleList.begin(); 
			it != particleList.end(); ++it)
		it->draw();
}

Rain::Thunder::Thunder(Coordinate2d start, Coordinate2d maxstride, int life)
	: life(life)
{
	Coordinate2d curpos = start;
	bool sign = true;

	vertices.push_back(start);

	while (curpos.y > ground->getYofX(curpos.x))
	{
		if (sign)
		{
			curpos = curpos - Coordinate2d(randomdUp(1,2) * maxstride.x, randomdUp(1,2) * maxstride.y);
		}
		else
		{
			curpos = curpos - Coordinate2d((-1) * randomdUp(1,2) * maxstride.x, (-1) * randomdDown(1,4) * maxstride.y);
		}

		vertices.push_back(curpos);
		sign = !sign;
	}
}

bool Rain::Thunder::recalc()
{
	return (--life > 0);
}

void Rain::Thunder::draw()
{
	for(int i = 0; i < (int) vertices.size() - 1; ++i)
		Line::draw(vertices[i], vertices[i+1], Color3d(1,1,1));
}

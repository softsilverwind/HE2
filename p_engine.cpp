#include <cstdio>
#include <list>
#include <cmath>
#include <climits>
#include <GL/glut.h>
#include "M_engine.h"
#include "BR_engine.h"
#include "p_engine.h"
#include "particle.h"
#include "structs.h"
#include "globals.h"

using namespace M_engine;

namespace HE2
{

using namespace std;

P_engine::P_engine(Coordinate2d position, int number, int time, double maxvel, Color3d color, Effect effect)
	: position(position)
{
	double tempvel, tempangle;

	TAG("p_engine");
	
	if (effect == CHAMPAGNE)
	{
		for (int i = 0; i < number; ++i)
		{
			tempvel = Random::randomd() * maxvel;
			tempangle = Random::randomd() * M_PI / 7 + 3 * M_PI / 7;
			Particle temp(position, Coordinate2d(Random::randomsgn() * tempvel * cos(tempangle), tempvel * sin(tempangle)), Coordinate2d(0,-0.0005), color, Random::randomi(time/4,time));
			particleList.push_back(temp);
		}
	}
	else
	{
		for (int i = 0; i < number; ++i)
		{
			tempvel = Random::randomd() * maxvel;
			tempangle = Random::randomd() * 2 * M_PI;
			Particle temp(position, Coordinate2d(Random::randomsgn() * tempvel * cos(tempangle), Random::randomsgn() * tempvel * sin(tempangle)), Coordinate2d(0,0), color, Random::randomi(time/4,time));
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

	TAG("rain");

	for (i = 0; i < number; ++i)
	{
		Coordinate2d position(Random::randomi(topleft.x, botright.x), Random::randomi(topleft.y, topleft.y + (topleft.y - botright.y)));
		Particle temp(position, Coordinate2d(0, -velocity), Coordinate2d(0,0), Color3d(0,0,1), INT_MAX);
		particleList.push_back(temp);
	}

	nextThunder = Random::randomi(500,5000);
}

bool Rain::recalc()
{
	for (vector<Particle>::iterator it = particleList.begin(); 
			it != particleList.end(); ++it)
	{
		if (!it->recalc())
		{
			Coordinate2d position(Random::randomi(topleft.x, botright.x), SIZEY);
			*it = Particle(position, Coordinate2d(0, -velocity), Coordinate2d(0,0), Color3d(0,0,1), INT_MAX);
		}
	}

	if (thunder)
		--nextThunder;

	if (!nextThunder)
	{
		nextThunder = Random::randomi(500,5000);
		D_engine::registerFull(new Thunder(Coordinate2d(Random::randomi(0,SIZEX), SIZEY), Coordinate2d(SIZEX/10, SIZEY/3), Random::randomi(500,1000)), NULL, true, true);
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

	TAG("thunder");

	vertices.push_back(start);

	while (curpos.y > ground->getYofX(curpos.x))
	{
		if (sign)
		{
			curpos = curpos - Coordinate2d(Random::randomdUp(1,2) * maxstride.x, Random::randomdUp(1,2) * maxstride.y);
		}
		else
		{
			curpos = curpos - Coordinate2d((-1) * Random::randomdUp(1,2) * maxstride.x, (-1) * Random::randomdDown(1,4) * maxstride.y);
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
		BR_engine::Line::draw(vertices[i], vertices[i+1], Color3d(1,1,1));
}

}

#ifndef __P_ENGINE_H__
#define __P_ENGINE_H__

#include <vector>
#include <list>
#include "structs.h"
#include "particle.h"
#include "d_engine.h"

namespace HE2
{

class P_engine : public Drawable
{
	public:
		typedef enum
		{
			CHAMPAGNE, FIREWORK
		}
		Effect;

	private:
		list<Particle> particleList;
		Coordinate2d position;
		
	public:
		P_engine(Coordinate2d position, int number, int time, double maxvel, Color3d color, Effect effect);

		void explode();

		bool recalc();
		void draw();
};

class Rain : public Drawable
{
	private:
		class Thunder : public Drawable
		{
			private:
				vector<Coordinate2d> vertices;
				int life;

			public:
				Thunder(Coordinate2d start, Coordinate2d maxstride, int life);
				bool recalc();
				void draw();
		};

		vector<Particle> particleList;
		Coordinate2d topleft, botright;
		double velocity;
		bool thunder;
		int nextThunder;

	public:
		Rain(Coordinate2d topleft, Coordinate2d botright, int number, double velocity, bool thunder);
		bool recalc();
		void draw();
};

}

#endif /* __P_ENGINE_H__ */

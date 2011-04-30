#include <iostream>
#include <sys/time.h>
#include <list>
#include <GL/glut.h>
#include "d_engine.h"
#include "serror.h"

using namespace std;

namespace HE2
{

list<D_engine::fullstruct> D_engine::full;
list<Drawable *> D_engine::drawOnly;
unsigned int D_engine::last_recalc = 0;

void D_engine::registerFull(Drawable *drawable, void (*onEnd)(), bool remove, bool destroy)
{
	if (destroy)
		remove = true;

	full.push_back(fullstruct(drawable, remove, destroy, onEnd));
}

void D_engine::registerDrawOnly(Drawable *drawable)
{
	drawOnly.push_back(drawable);
}

void D_engine::draw()
{
	for (list<Drawable *>::iterator it = drawOnly.begin(); it != drawOnly.end(); ++it)
		(*it)->draw();

	for (list<fullstruct>::iterator it = full.begin(); it != full.end(); ++it)
	{
		if (it->invalid)
		{
			delete it->drawable;
			full.erase(it--);
			continue;
		}
		
		it->drawable->draw();
	}
}

void D_engine::recalc()
{
	unsigned int time_now = glutGet(GLUT_ELAPSED_TIME);

	#ifdef __DEBUG__
		static int fails = 0;
		struct timeval before, after;
		double msecs;
	#endif

	for (unsigned int i = 0; i < time_now - last_recalc; ++i)
	{
		#ifdef __DEBUG__
			gettimeofday(&before, NULL);
		#endif

		for (list<fullstruct>::iterator it = full.begin(); it != full.end(); ++it)
		{
			if (it->invalid)
			{
				delete it->drawable;
				full.erase(it--);
				continue;
			}

			if (!(it->drawable->recalc()))
			{
				if (it->onEnd)
					it->onEnd();

				if (it->destroy)
					delete it->drawable;
				
				if (it->remove)
					full.erase(it--);
			}
		}

		#ifdef __DEBUG__
			gettimeofday(&after, NULL);
			msecs = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_usec - before.tv_usec) / 1000.0;
			if (msecs > 1)
			{
				++fails;
			}
			else
			{
				fails = 0;
			}

			if (fails == 2)
				serror(SE_NOTIFY, "Exceeding 1msec per recalc twice in a row!");
			else if (fails == 10)
				serror(SE_WARNING, "Exceeded 1msec 10 times in a row!!");
			else if (fails == 100)
			{
				serror(SE_INTERNAL, "Exceeded 1msec 20 times in a row, aborting!");
				throw 42;
			}
		#endif
	}
	last_recalc = time_now;
}

void D_engine::unregisterDrawOnly(Drawable *drawable)
{
	for (list<Drawable *>::iterator it = drawOnly.begin(); it != drawOnly.end(); ++it)
		if (*it == drawable)
		{
			drawOnly.erase(it);
			delete drawable;
			break;
		}
}

void D_engine::unregisterFull(Drawable *drawable)
{
	for (list<fullstruct>::iterator it = full.begin(); it != full.end(); ++it)
		if (it->drawable == drawable)
		{
			it->invalid = true;
			break;
		}
}

}

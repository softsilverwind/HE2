#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <string>
#include <list>
#include <cassert>
#include "serror.h"

using namespace std;

namespace HE2
{

class Drawable
{
	public:
		virtual void draw() = 0;
		virtual bool recalc() { assert(0); }
		string tag;
};

class D_engine
{
	private:
		typedef struct fullstruct_tag
		{
			Drawable *drawable;
			bool invalid;
			bool remove;
			bool destroy;
			void (*onEnd)();
			fullstruct_tag (Drawable *drawable, bool remove, bool destroy, void (*onEnd)())
				: drawable(drawable), invalid(false), remove(remove), destroy(destroy), onEnd(onEnd) {};
		}
		fullstruct;

		static list<fullstruct> full;
		static list<Drawable *> drawOnly;
		static unsigned int last_recalc;

	public:
		static void registerFull(Drawable *drawable, void (*onEnd)() = NULL, bool remove = false, bool destroy = false);
		static void registerDrawOnly(Drawable *drawable);

		static void unregisterDrawOnly(Drawable *drawable);
		static void unregisterFull(Drawable *drawable);

		static void draw();
		static void recalc();
};

}

#endif /* __DISPLAY_H__ */

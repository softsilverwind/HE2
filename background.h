#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "structs.h"
#include "d_engine.h"

namespace HE2
{

class Background : public Drawable
{
	private:
		Color3d colorh, colorl;
	
	public:
		Background(Color3d high, Color3d low);

		void draw();
};

}

#endif

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <starlia.h>

using namespace Starlia;

class Background : public StarObject
{
	private:
		Color3d colorh, colorl;
	
	public:
		Background(Color3d high, Color3d low);

		void draw();
};

#endif

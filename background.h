#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <starlia.h>

using namespace Starlia;

class Background : public StarObject
{
	private:
		Color3f colorh, colorl;
	
	public:
		Background(Color3f high, Color3f low);

		void draw();
};

#endif

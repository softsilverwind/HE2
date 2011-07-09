#include <iostream>
#include <sstream>
#include <cstdlib>
#include <starlia.h>

#include <SDL/SDL_mixer.h>

#include "structs.h"
#include "background.h"
#include "ground.h"
#include "person.h"
#include "dud.h"
#include "p_engine.h"
#include "globals.h"

using namespace std;
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
StarObjectLayer *layer[3];
StarWidgetLayer *canvas, *widgets, *menu;
Mix_Chunk *explosion;

Person *player[2];
bool firing;
bool iHasAKill = false;
Rain *rain;

unsigned int last_recalc;

StarLabel *scoreLabel[2];

void init();

void changePlayer()
{
	player[currPlayer]->closeLaser();
	currPlayer = (currPlayer + 1) % 2;
	firing = false;
}

void printScore()
{
	stringstream ss[2];
       	ss[0] << score[0];
       	ss[1] << score[1];
	scoreLabel[0]->chText(string(ss[0].str()));
	scoreLabel[1]->chText(string(ss[1].str()));
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
			cerr << "We should not have come here, heh" << endl;
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

void mouse(Coordinate2d pos)
{
	pos.x *= SIZEX;
	pos.y *= SIZEY;
	player[currPlayer]->pointWeapon(pos.x,SIZEY - pos.y);
}

void click(Coordinate2d pos)
{
	pos.x *= SIZEX;
	pos.y *= SIZEY;

	player[currPlayer]->pointWeapon(pos.x,SIZEY - pos.y);

	if (!firing)
	{
		layer[2]->registerObject(player[currPlayer]->fire());
		firing = true;
	}
}

void myMenu(Coordinate2d pos)
{
	StarCore::registerLayerForeground(menu);
}

void myGoOn2(Coordinate2d pos)
{
	StarCore::unregisterLayer(menu);
}

void myExit(Coordinate2d pos)
{
	exit(0);
}

void myGoOn(Coordinate2d pos)
{
	StarCore::unregisterLayer(menu);
	menu->clearLayer();
        menu->registerObject(new StarLabel("PLAY", Coordinate2d(20, 60), Coordinate2d(80, 50), 4, Color3d(0,1,0), StarLabel::CENTER, myGoOn2));
	menu->registerObject(new StarLabel("EXIT", Coordinate2d(20, 20), Coordinate2d(80, 10), 4, Color3d(0,1,0), StarLabel::CENTER, myExit));

	widgets = new StarWidgetLayer(Coordinate2d(100, 100));
	canvas = new StarWidgetLayer(Coordinate2d(100, 100));
	canvas->registerObject(new StarWidget(Coordinate2d(0,100), Coordinate2d(100, 0), click, mouse));
	widgets->registerObject(new StarLabel("MENU", Coordinate2d(90, 4), Coordinate2d(100, 0), 3, Color3d(0,0,1), StarLabel::CENTER, myMenu));

	widgets->registerObject(new StarLabel("Player 1:", Coordinate2d(2, 98), Coordinate2d(30, 94), 3, Color3d(0,1,0), StarLabel::RIGHT));
	widgets->registerObject(new StarLabel("Player 2:", Coordinate2d(2, 94), Coordinate2d(30, 90), 3, Color3d(1,0,0), StarLabel::RIGHT));
	widgets->registerObject(scoreLabel[0] = new StarLabel("0", Coordinate2d(32, 98), Coordinate2d(60, 94), 3, Color3d(0,1,0), StarLabel::LEFT));
	widgets->registerObject(scoreLabel[1] = new StarLabel("0", Coordinate2d(32, 94), Coordinate2d(60, 90), 3, Color3d(1,0,0), StarLabel::LEFT));

	StarCore::registerLayerForeground(canvas);
	StarCore::registerLayerForeground(widgets);

	layer[0] = new StarObjectLayer(Coordinate2d(800, 600));
	layer[1] = new StarObjectLayer(Coordinate2d(800, 600));
	layer[2] = new StarObjectLayer(Coordinate2d(800, 600));
	StarCore::registerLayerBackground(layer[0]);
	StarCore::registerLayerBackground(layer[1]);
	StarCore::registerLayerBackground(layer[2]);

	/* begin starlia integration block */

	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
	 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		cerr << "Unable to initialize audio" << endl;
		exit(1);
	}

	Mix_Music *music = Mix_LoadMUS("desert fight loop.ogg");
	explosion = Mix_LoadWAV("explosion.wav");
	Mix_PlayMusic(music, -1);

	/* end starlia integration block */

	init();
}

int main(int argc, char** argv)
{
	menu = new StarWidgetLayer(Coordinate2d(100, 100), true);

	StarCore::registerLayerForeground(menu);
	menu->registerObject(new StarLabel("Welcome to the HE Training Grounds", Coordinate2d(20, 90), Coordinate2d(80, 70), 4, Color3d(1,1,0), StarLabel::CENTER));
        menu->registerObject(new StarLabel("PLAY", Coordinate2d(20, 60), Coordinate2d(80, 50), 4, Color3d(0,1,0), StarLabel::CENTER, myGoOn));
	menu->registerObject(new StarLabel("EXIT", Coordinate2d(20, 20), Coordinate2d(80, 10), 4, Color3d(0,1,0), StarLabel::CENTER, myExit));


	StarCore::init("HE Training Grounds 2 v1.00-beta1", SIZEX, SIZEY);


	StarCore::loop();

	return 0;
}

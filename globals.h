#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <starlia.h>
#include "ground.h"
#include "person.h"

#define SIZEX 800
#define SIZEY 600

#define PARTICLES 500
#define TIME 100
#define SPEED 5


extern Ground *ground;
extern StarObjectLayer *layer[3];
extern Ground *ground;
extern Person *player[2];
extern unsigned int score[2];

void changePlayer();
void reInit();

#endif /* __GLOBAL_H__ */

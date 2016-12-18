#ifndef _SPLASH_WATER
#define _SPLASH_WATER

#include "sprite.h"

class CSplashWater:public CSprite
{
private:
	bool _End;
public:
	bool isEnd();
	void load(char* filepath, float x, float y);
	void update(int);
};

#endif
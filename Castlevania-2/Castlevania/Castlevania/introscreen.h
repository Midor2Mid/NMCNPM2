#ifndef _INTRO_H
#define _INTRO

#include "sprite.h"

class cintro
{
private:
	CSprite simon;
	CSprite introscreen;
	CSprite helicopter;
	CSprite bat;
	int _WaitingCount;

	CSound			*intro;
public:
	bool isend;
	void initialize();
	void update(int delta);
	void render(int delta);
	void renderText(int delta);
};

#endif
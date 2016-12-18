#ifndef _SNAKE_H
#define _SNAKE_H

#include "sprite.h"

class csnake:public CSprite
{
private:
	int _Status;
public:
	int isActive();
	void setStatus(int stt);
	void update(int delta);
};

#endif
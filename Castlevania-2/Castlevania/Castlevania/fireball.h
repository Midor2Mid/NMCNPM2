#ifndef _FIREBALL_H
#define _FIREBALL_H

#include "sprite.h"

class cfireball:public CSprite
{
private:
	int _Status;
public:
	int isActive();
	void update(int delta);
};

#endif
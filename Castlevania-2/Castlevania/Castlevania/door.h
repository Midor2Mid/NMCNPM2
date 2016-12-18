#ifndef DOOR_H
#define DOOR_H

#include "sprite.h"

class CDoor :public CSprite
{
private:
public:
	void load(char*);
	void update(int, int);
};

#endif // !DOOR_H

#include "door.h"

void CDoor::load(char* filepath)
{
	CSprite::load(filepath, 2, 1);
	animate(false);
}

void CDoor::update(int delta, int id)
{
}
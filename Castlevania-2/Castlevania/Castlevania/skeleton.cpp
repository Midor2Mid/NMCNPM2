#include "skeleton.h"

void CSkeleton::load(char* filepath)
{
	CSprite::load(filepath, 4, 1);
}

void CSkeleton::update(int delta, int id)
{
	if (CSprite::isFlip())
		CSprite::moveX(delta, id);
	else
		CSprite::moveX(-delta, id);
}
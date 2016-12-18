#ifndef _SKELETON_H
#define _SKELETON_H

#include "sprite.h"

class CSkeleton:public CSprite{
	void load(char*);
	void update(int, int);
};
#endif // !_SKELETON

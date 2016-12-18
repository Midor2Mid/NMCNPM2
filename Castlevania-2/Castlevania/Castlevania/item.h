#ifndef _ITEM_H
#define _ITEM_H

#include "sprite.h"

class citem :public CSprite
{
private:
	int invisibletime;
	
public:
	int type;
	int status;
	citem();
	~citem();
	void load(char* filepath, int columns, int rows, int type);
	void update(int delta);
	void render(int delta);
};

#endif _ITEM_H
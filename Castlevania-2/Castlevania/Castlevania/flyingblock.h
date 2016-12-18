#ifndef _FLYINGBLOCK_H
#define _FLYINGBLOCK_H

#include "sprite.h"

class cflyingblock :public CSprite
{
private:
	vector<int> _Status;
public:
	void	load(char*filepath);
	void	setStatus(int id, int status);
	void	update(int delta, int id);
	void	addNewObject(int id, float x, float y, float width, float height, int flip);
	int		isActive(int);
	void	ClearAll();
};

#endif
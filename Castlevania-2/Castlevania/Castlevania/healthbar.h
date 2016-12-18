#ifndef		_HEALTH_BAR_H
#define		_HEALTH_BAR_H

#include "sprite.h"

class chealthbar:public CSprite
{
private:
	int bosshealth;
	int emptybosshealth;
	int emptysimonhealth;
	int simonhealth;
	int maxhealth;
	vector<Box> simonhealthbox;
	vector<int> simonhealthframe;
	vector<Box> bosshealthbox;
	vector<int> bosshealthframe;
	void _draw(Box bx, int tile);
public:
	void load(char* filepath, float x, float y);
	void update(int delta, int bosshealth);
	void render(int delta);
};
#endif		_HEALTH_BAR_H
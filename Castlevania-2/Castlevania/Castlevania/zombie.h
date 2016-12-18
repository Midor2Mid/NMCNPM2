#ifndef ZOMBIE_H
#define	ZOMBIE_H
#include "sprite.h"

class CZombie :public CSprite
{
private:
	vector<int> _Status;
public:
	void addNewObject(int id, float x, float y, float width, float height, int);
	void load(char*);
	void update(int, int);
	void ClearAll();
	int isActive(int);
};

#endif // !ZOMBIE_H

#ifndef _ARMOR_EVIL
#define	_ARMOR_EVIL

#include "sprite.h"

class CArmorevil:public CSprite
{
private:
	
public:
	vector<int> _Status;
	vector<int> health;
	vector<int> invulnerabletime;
	vector<int> invulnerable;
	void	addNewObject(int id, float x, float y, float width, float height, int flip);
	void	setStatus(int stt, int id);
	int		isActive(int id);
	void	ClearAll();
	void	load(char* filepath);
	void	update(int delta, int id);
	int		render(int delta, int id);
};

#endif
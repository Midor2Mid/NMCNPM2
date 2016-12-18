#ifndef _CAT_DEMON_H
#define _CAT_DEMON_H

#include "sprite.h"

class CCat: public CSprite
{
private:
	vector<int>		_Status;
	vector<int>		_Currentframe;
	vector<int>		_Startframe;
	vector<int>		_Lastframe;
	int				_Animationdelay;
	vector<int>		_AnimationTick;
public:
	void	ClearAll();
	void	addNewObject(int id, float x, float y, float width, float height, int );
	void	load(char*);
	void	update(int, int);
	int		render(int, int);
	void	flip(int, float, float, int);
	void	draw(int, float, float, int);
	void	animate(int, int, int, int);
	void	animate(int, int);
	void	setStatus(int, int);
	int		isActive(int);
	
};

#endif
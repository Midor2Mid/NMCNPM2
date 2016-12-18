#ifndef _FISHMONSTER_H
#define _FISHMONSTER_H

#include "sprite.h"

class CFish:public CSprite{
private:
	vector<int>		_Status;
	vector<int>		_Currentframe;
	vector<int>		_Startframe;
	vector<int>		_Lastframe;
	int				_Animationdelay;
	vector<int>		_AnimationTick;
	vector<float>	_TempHeight;
	CSound			*splashingwatersound;
public:
	void	ClearAll();
	void	addNewObject(int id, float x, float y, float width, float height, int flip); // them mot vat the
	void	load(char*);
	void	update(int, int);
	int		render(int, int);
	void	flip(int, float, float, int);
	void	draw(int, float, float, int);
	void	specificrender(int, float, float, int, float);
	void	specificfliprender(int, float, float, int, float);
	void	animate(int, int, int, int);
	void	animate(int, int);
	void	setStatus(int, int);
	int		isActive(int);
};

#endif
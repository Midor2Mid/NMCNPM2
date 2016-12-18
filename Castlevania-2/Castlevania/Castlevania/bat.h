#ifndef _BAT_H
#define _BAT_H
#include "sprite.h"

class CBat :public CSprite
{
private:
	int _TempMoveY = 0;
	bool _InvertMove = false;
	float _Range = 100;
	vector<int>	_Status;
	vector<int>		_Currentframe;
	vector<int>		_Startframe;
	vector<int>		_Lastframe;
	int				_Animationdelay;
	vector<int>		_AnimationTick;
public:
	CBat(); 
	void load(char*);
	~CBat();
	void	ClearAll();
	int		render(int delta, int id);
	void	addNewObject(int id, float x, float y, float width, float height, int flip);
	void	moveLikeJagger(int delta, int id);
	void	update(int delta, int id);
	void	flip(int delta, float x , float y, int pos);
	void	draw(int delta, float x , float y, int pos);
	void	animate(int animatedelay, int startframe, int lastframe, int id);
	void	animate(int delta, int id);
	int		isActive(int id);
};

#endif

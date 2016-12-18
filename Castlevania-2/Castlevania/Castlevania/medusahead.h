#ifndef _MEDUSA_HEAD
#define _MEDUSA_HEAD

#include "sprite.h"
class CMedusahead:public CSprite
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
	CMedusahead();
	void load(char*);
	~CMedusahead();
	void	ClearAll();
	int		render(int delta, int id);
	void	addNewObject(int id, float x, float y, float width, float height, int flip);
	void	moveLikeJagger(int delta, int id);
	void	update(int delta, int id);
	void	flip(int delta, float x, float y, int pos);
	void	draw(int delta, float x, float y, int pos);
	void	animate(int animatedelay, int startframe, int lastframe, int id);
	void	animate(int delta, int id);
	int		isActive(int id);
};
#endif
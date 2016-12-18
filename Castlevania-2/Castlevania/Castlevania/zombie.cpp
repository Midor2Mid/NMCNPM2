#include "zombie.h"

void CZombie::load(char*filepath)
{
	CSprite::load(filepath, 2, 1);
	animate(true);
	animate(45, 0, 1); 
	_Status.push_back(false);
}

void CZombie::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(0);
}
void CZombie::ClearAll()
{
	CSprite::ClearAll();
	_Status.clear();
}

int CZombie::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void CZombie::update(int delta, int id)
{
	int position = findVectorPosition(id);
	if (_Status.at(position) != 0 && _Status.at(position) != 100)
	{
		if (cmr.pos.x + SCREENWIDTH + 300 < getX(id) || cmr.pos.x - 300 > getX(id))
		{
			_Status.at(position) = 100;
		}
	}

	switch (_Status.at(position))
	{
	case 0:
		if (cmr.pos.x + SCREENWIDTH > _Box.at(position).x && cmr.pos.x < _Box.at(position).x + _Box.at(position).w && cmr.pos.y > _Box.at(position).y && cmr.pos.y - SCREENHEIGHT < _Box.at(position).y + _Box.at(position).h)
		{
			_Status.at(position) = 1;
		}
		break;
	case 1:
		if (CSprite::isFlip(id))
		{
			CSprite::moveX(delta, id);
		}
		else
		{
			CSprite::moveX(-delta, id);
		}
		break;
	case 2:
		_Box.at(position).vx = 0;
		_Box.at(position).vy -= 0.2;
		break;
	}
}
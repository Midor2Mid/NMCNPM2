#include "fireball.h"

int cfireball::isActive()
{
	return _Status;
}

void cfireball::update(int delta)
{
	if (_Status != 0)
	{
		if (cmr.pos.x + SCREENWIDTH + 500 < getX() || cmr.pos.x - 500 > getX())
		{
			_Status = 100;
		}
	}
	
	switch (_Status)
	{
	case 0:
		_Box.at(0).vx = 0;
		_Box.at(0).vy = 0;
		if (cmr.pos.x + SCREENWIDTH > getX() && cmr.pos.x < getX())
			_Status = 1;
		break;
	case 1:
		if (isFlip())
			_Box.at(0).vx = 4;
		else
			_Box.at(0).vx = -4;
		break;
	}
	_Box.at(0).x += _Box.at(0).vx;
	_Box.at(0).y += _Box.at(0).vy;
}
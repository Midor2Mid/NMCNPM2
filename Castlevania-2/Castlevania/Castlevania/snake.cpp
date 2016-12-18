#include "snake.h"

int csnake::isActive()
{
	return _Status;
}

void csnake::setStatus(int stt)
{
	_Status = stt;
}

void csnake::update(int delta)
{
	animate(true);
	animate(25, 0, 1, 1);
	switch (_Status)
	{
	case 0:
		_Box.at(0).vx = 0;
		_Box.at(0).vy = 0;
		break;

	case 1:
		_Box.at(0).vy = 0;
		if (isFlip())
			_Box.at(0).vx = 4;
		else
			_Box.at(0).vx = -4;
		break;
	case 2:
		_Box.at(0).vx = 0;
		_Box.at(0).vy -= 0.2;
		break;
	}
	_Box.at(0).x += _Box.at(0).vx;
	_Box.at(0).y += _Box.at(0).vy;
}
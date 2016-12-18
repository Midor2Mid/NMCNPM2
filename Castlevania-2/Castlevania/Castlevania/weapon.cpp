#include "weapon.h"

cweapon::cweapon()
{
	_Type = 0;
	animate(true);
	_Waitingtime = 0;
}

cweapon::~cweapon()
{
}

void cweapon::load(char* filepath, int columns, int rows)
{
	CSprite::load(filepath, columns, rows);
}

int cweapon::getType()
{
	return _Type;
}

void cweapon::setType(int type)
{
	_Type = type;
}

void cweapon::update(int delta)
{
	if (_Status != 0 && _Status != 100)
	{
		if (cmr.pos.x + SCREENWIDTH + 50 < getX() || cmr.pos.x - 50 > getX()||cmr.pos.y - SCREENHEIGHT + 20 > getY())
		{
			_Status = 100;
		}
	}

	switch (_Type)
	{
	case 1:
		switch (_Status)
		{
		case 0:
			_Box.at(0).vx = 0;
			_Box.at(0).vy = 0;
			break;
		case 1:
			if (isFlip())
				_Box.at(0).vx = -8;
			else
				_Box.at(0).vx = 8;
			break;
		}
		break;
	case 2:
		switch (_Status)
		{
		case 0:
			//_Box.at(0).vx = 0;
			//_Box.at(0).vy = 0;
			break;
		case 1:
			if (isFlip())
			{
				_Box.at(0).vx = -3;
				_Box.at(0).vy -= 0.5;
			}
			else
			{
				_Box.at(0).vx = 3; 
				_Box.at(0).vy -= 0.5;
			}
			break;
		case 2:
			_Box.at(0).vx = 0;
			_Box.at(0).vy = 0;
			_Waitingtime += delta;
			animate(90, 1, 2);
			if (_Waitingtime > 800)
			{
				_Waitingtime = 0;
				animate(300, 0, 0);
				setStatus(100);
			}
			animate(delta);
			break;
		}
		break;
	case 3:
		switch (_Status)
		{
		case 0:
			_Box.at(0).vx = 0;
			_Box.at(0).vy = 0;
			break;
		case 1:
			animate(20, 0, 3);
			if (isFlip())
			{
				_Box.at(0).vx = -3;
				_Box.at(0).vy -= 0.5;
			}
			else
			{
				_Box.at(0).vx = 3;
				_Box.at(0).vy -= 0.5;
			}
			animate(delta);
			break;
		}
		break;
	case 4:
		switch (_Status)
		{
		case 0:
			_Box.at(0).vx = 0;
			_Box.at(0).vy = 0;
			break;
		case 1:
			if (isFlip())
			{
				_Box.at(0).vx = -7;
				_Status = 2;
			}
			else
			{
				_Box.at(0).vx = 7;
				_Status = 2;
			}
			break;
		case 2:
			animate(10, 0, 2);
			if (isFlip())
			{
				_Box.at(0).vx += 0.15;
				if (_Box.at(0).vx > 8)
					_Box.at(0).vx = 8;
			}
			else
			{
				_Box.at(0).vx -= 0.15;
				if (_Box.at(0).vx < -8)
					_Box.at(0).vx = -8;
			}
			animate(delta);
			break;
		}
		break;
	}

	_Box.at(0).x += _Box.at(0).vx;
	_Box.at(0).y += _Box.at(0).vy;
}

void cweapon::setStatus(int stt)
{
	_Status = stt;
}

int cweapon::getStatus()
{
	return _Status;
}
#include "splashwater.h"

void CSplashWater::load(char* filepath, float x, float y)
{
	CSprite::load(filepath, 1, 1);
	ClearAll();
	for (int i = 0; i < 3; i++)
	{
		addNewObject(i, x, y, getWidth(),getHeight(), 0);
	}
	_Box.at(0).vy = 11;
	_Box.at(1).vy = 13;
	_Box.at(2).vy = 12;
	_End = false;
}

bool CSplashWater::isEnd()
{
	return _End;
}

void CSplashWater::update(int delta)
{
	_Box.at(0).vy -= 0.9;
	_Box.at(1).vy -= 1.1;
	_Box.at(2).vy -= 0.8;
	if (_Box.at(0).vy > 0)
		_Box.at(0).vx = -5;
	else
		_Box.at(0).vx = 0;
	if (_Box.at(1).vy > 0)
		_Box.at(1).vx = 8;
	else
		_Box.at(1).vx = 0;
	_Box.at(0).x += _Box.at(0).vx;
	_Box.at(0).y += _Box.at(0).vy;
	_Box.at(1).x += _Box.at(1).vx;
	_Box.at(1).y += _Box.at(1).vy;
	_Box.at(2).x += _Box.at(2).vx;
	_Box.at(2).y += _Box.at(2).vy;
	if (_Box.at(0).vy < -30)
	{
		_End = true;
	}
}
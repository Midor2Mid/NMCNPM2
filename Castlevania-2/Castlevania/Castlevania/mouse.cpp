#include "Mouse.h"

Mouse::Mouse()
{
	_CurrentState = false;
	_PreviousState = false;
}

Mouse::~Mouse()
{
}

void Mouse::load()
{
	CSprite::load("resource/image/mousecursor.png", 3, 1);
	setNonFlip(1);
	_Box.at(0).y += _Box.at(0).h;
	_Box.at(0).w = 1;
	_Box.at(0).h = 1;
	setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
}

float Mouse::getX()
{
	return _Box.at(0).x;
}

float Mouse::getY()
{
	return _Box.at(0).y;
}

camera Mouse::getCurrentCamera()
{
	if (getCamera() == 1)
		return cmr2;
	return cmr;
}

void Mouse::setCurrentState(bool current)
{
	_CurrentState = current;
}

bool Mouse::getCurrentState()
{
	return _CurrentState;
}

void Mouse::setPreviousState(bool previous)
{
	_PreviousState = previous;
}

bool Mouse::getPreviousState()
{
	return _PreviousState;
}

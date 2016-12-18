#include "flyingblock.h"

void cflyingblock::load(char*filepath)
{
	CSprite::load(filepath, 1, 1);
	_Status.push_back(0);
	_Box.at(0).vx = 2;
}

void cflyingblock::setStatus(int id, int status)
{
	_Status.at(findVectorPosition(id)) = status;
}

int	cflyingblock::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void cflyingblock::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(0);
	_Box.at(findVectorPosition(id)).vx = 2;
}

void cflyingblock::ClearAll()
{
	CSprite::ClearAll();
	_Status.clear();
}


void cflyingblock::update(int delta, int id)
{
	int vectorposition = findVectorPosition(id);
	switch (_Status.at(vectorposition))
	{
	case 0:
		_Box.at(vectorposition).vx += 0.1;
		if (_Box.at(vectorposition).vx > 2)
			_Box.at(vectorposition).vx = 2;
		break;
	case 1:
		_Box.at(vectorposition).vx -= 0.1;
		if (_Box.at(vectorposition).vx < -2)
			_Box.at(vectorposition).vx = -2;
		break;
	case 2:
		break;
	}
	_Box.at(vectorposition).x += _Box.at(vectorposition).vx;
}

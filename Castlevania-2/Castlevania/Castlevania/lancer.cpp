#include "lancer.h"

void CLancer::load(char* filepath)
{
	CSprite::load(filepath, 4, 1);
	_Status.push_back(0);
	invulnerabletime.push_back(0);
	invulnerable.push_back(0);
	health.push_back(2);
	animate(true);
	animate(60, 0, 3);
}

void CLancer::ClearAll()
{
	CSprite::ClearAll();
	_Status.clear();
	invulnerabletime.clear();
	invulnerable.clear();
	health.clear();
}

void CLancer::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(0);
	invulnerabletime.push_back(0);
	invulnerable.push_back(0);
	health.push_back(2);
}

void CLancer::setStatus(int stt, int id)
{
	_Status.at(findVectorPosition(id)) = stt;
}

int CLancer::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void CLancer::update(int delta, int id)
{
	int vectorposition = findVectorPosition(id);
	if (_Status.at(vectorposition) != 0)
	{
		if (cmr.pos.x + SCREENWIDTH + 500 < getX(id) || cmr.pos.x - 500 > getX(id))
		{
			_Status.at(vectorposition) = 100;
		}
	}

	switch (_Status.at(vectorposition))
	{
	case 0:
		_Box.at(vectorposition).vx = 0;
		_Box.at(vectorposition).vy = 0;
		if (cmr.pos.x + SCREENWIDTH > getX(id) && cmr.pos.x < getX(id))
			_Status.at(vectorposition) = 1;
		break;
	case 1:
		_Box.at(vectorposition).vy = 0;

		if (isFlip(id))
			_Box.at(vectorposition).vx = 0.7;
		else
			_Box.at(vectorposition).vx = -0.7;

		break;
	case 2:
		_Box.at(vectorposition).vx = 0;
		_Box.at(vectorposition).vy -= 0.5;
		break;
	}
	_Box.at(vectorposition).x += _Box.at(vectorposition).vx;
	_Box.at(vectorposition).y += _Box.at(vectorposition).vy;
}

int CLancer::render(int delta, int id)
{
	int vectorposition = findVectorPosition(id);
	if (invulnerable.at(vectorposition))
	{
		invulnerabletime.at(vectorposition) += delta;
		if (invulnerabletime.at(vectorposition) > 140)
		{
			invulnerable.at(vectorposition) = 0;
			invulnerabletime.at(vectorposition) = 0;
		}
	}
	return CSprite::render(delta, id);
}
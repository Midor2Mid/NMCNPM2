#include "ghost.h"

void CGhost::load(char* filepath)
{
	CSprite::load(filepath, 2, 1);
	_Status.push_back(0);
	invulnerabletime.push_back(0);
	invulnerable.push_back(0);
	health.push_back(6);
	animate(true);
	a.push_back(0);
}

void CGhost::getSimonbox(Box simonbox)
{
	_simonbox.x = simonbox.x;
	_simonbox.y = simonbox.y;
}

void CGhost::ClearAll()
{
	CSprite::ClearAll();
	_Status.clear();
	invulnerabletime.clear();
	invulnerable.clear();
	health.clear();
}

void CGhost::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(0);
	invulnerabletime.push_back(0);
	invulnerable.push_back(0);
	health.push_back(6);
	a.push_back(0);
}

void CGhost::setStatus(int stt, int id)
{
	_Status.at(findVectorPosition(id)) = stt;
}

int CGhost::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void CGhost::update(int delta, int id)
{
	int vectorposition = findVectorPosition(id);
	if (_Status.at(vectorposition) != 0)
	{
		if (cmr.pos.x + SCREENWIDTH + 500 < getX(id) || cmr.pos.x - 500 > getX(id))
		{
			_Status.at(vectorposition) = 100;
		}
	}
	if (invulnerable.at(vectorposition))
	{
		invulnerabletime.at(vectorposition) += delta;
		if (invulnerabletime.at(vectorposition) > 140)
		{
			invulnerable.at(vectorposition) = 0;
			invulnerabletime.at(vectorposition) = 0;
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
		float deltax = _Box.at(vectorposition).x - _simonbox.x;
		float deltay = _Box.at(vectorposition).y - _simonbox.y;
		if (deltax == 0)
			a.at(vectorposition) = 0;
		else
			a.at(vectorposition) = deltay / deltax;
		if (_Box.at(vectorposition).x < _simonbox.x)
			_Box.at(vectorposition).vx = 0.5;
		else
			_Box.at(vectorposition).vx = -0.5;
		float nextx = deltax + _Box.at(vectorposition).vx;
		float nexty = a.at(vectorposition) * nextx;
		_Box.at(vectorposition).vy = nexty - deltay;
		if (_Box.at(vectorposition).vy > 0.5)
			_Box.at(vectorposition).vy = 0.5;
		if (_Box.at(vectorposition).vy < -0.5)
			_Box.at(vectorposition).vy = -0.5;
		break;
	}
	if (_Box.at(vectorposition).vx > 0)
	{
		_Flip.at(vectorposition) = 1;
	}
	else
	{
		_Flip.at(vectorposition) = 0;
	}
	_Box.at(vectorposition).x += _Box.at(vectorposition).vx;
	_Box.at(vectorposition).y += _Box.at(vectorposition).vy;
}

int CGhost::render(int delta, int id)
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
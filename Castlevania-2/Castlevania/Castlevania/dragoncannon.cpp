#include "dragoncannon.h"

void CDragonCannon::load(char* filepath)
{
	CSprite::load(filepath, 1, 1);
	_Status.push_back(0);
	invulnerabletime.push_back(0);
	invulnerable.push_back(0);
	health.push_back(6);
	animate(false);
	_fire.load("resource/image/fireball.png", 1, 1);

	_WaitingFiring.push_back(0);
	_WaitingFire.push_back(0);
	_LimitFireBall = 2;
	vector<cfireball> f;
	fire.push_back(f);
}

void CDragonCannon::getSimonbox(Box simonbox)
{
	_simonbox.x = simonbox.x;
	_simonbox.y = simonbox.y;
}

void CDragonCannon::ClearAll()
{
	CSprite::ClearAll();
	_Status.clear();
	invulnerabletime.clear();
	invulnerable.clear();
	health.clear();
	_WaitingFiring.clear();
	_WaitingFire.clear();
	fire.clear();
}

void CDragonCannon::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(0);
	invulnerabletime.push_back(0);
	invulnerable.push_back(0);
	health.push_back(6);

	_WaitingFiring.push_back(0);
	_WaitingFire.push_back(0);
	_LimitFireBall = 2;
	vector<cfireball> f;
	fire.push_back(f);
}

void CDragonCannon::setStatus(int stt, int id)
{
	_Status.at(findVectorPosition(id)) = stt;
}

int CDragonCannon::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void CDragonCannon::update(int delta, int id)
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
		_WaitingFiring.at(vectorposition) += delta;
		if (_LimitFireBall > fire.at(vectorposition).size())
		{
			if (_WaitingFiring.at(vectorposition) > 700)
			{
				_WaitingFiring.at(vectorposition) = 0;
				if (_simonbox.x < getX(id))
				{
					_fire.setFlip(0);
					if (isFlip(id))
						_fire.setPosition(getX(id), getY(id) - 15);
					else
						_fire.setPosition(getX(id), getY(id) + 15);

				}
				else
				{
					_fire.setFlip(1);
					if (isFlip(id))
						_fire.setPosition(getX(id), getY(id) + 15);
					else
						_fire.setPosition(getX(id), getY(id) - 15);
				}
				fire.at(vectorposition).push_back(_fire);
			}
		}
		_Box.at(vectorposition).vy = 0;
		_Box.at(vectorposition).vx = 0;
		break;
	}
	for (int i = 0; i < fire.at(vectorposition).size(); i++)
	{
		fire.at(vectorposition).at(i).update(delta);
		if (fire.at(vectorposition).at(i).isActive() == 100)
		{
			fire.at(vectorposition).erase(fire.at(vectorposition).begin() + i);
			i--;
		}
	}
}

int CDragonCannon::render(int delta, int id)
{
	CSprite::render(delta, id);
	int vectorposition = findVectorPosition(id);
	for (int i = 0; i < fire.at(vectorposition).size(); i++)
		fire.at(vectorposition).at(i).render(delta);

	if (invulnerable.at(vectorposition))
	{
		invulnerabletime.at(vectorposition) += delta;
		if (invulnerabletime.at(vectorposition) > 140)
		{
			invulnerable.at(vectorposition) = 0;
			invulnerabletime.at(vectorposition) = 0;
		}
	}
	return 0;
}

vector<Box> CDragonCannon::getListFire(int id)
{
	int vectorposition = findVectorPosition(id);
	vector<Box> bx;
	for (int i = 0; i < fire.at(vectorposition).size(); i++)
	{
		bx.push_back(fire.at(vectorposition).at(i).getBox());
	}

	return bx;
}
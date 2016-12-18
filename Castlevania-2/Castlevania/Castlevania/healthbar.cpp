#include "healthbar.h"

void chealthbar::load(char* filepath, float x, float y)
{
	CSprite::load(filepath, 3, 1);
	maxhealth = 20;
	for (int i = 0; i < maxhealth; i++)
	{
		float boxX = x - maxhealth/2 * getWidth() - getWidth() / 2;
		boxX = x + i * getWidth();
		float boxY = y - getHeight();
		Box bx(boxX, boxY, getWidth(), getHeight());
		simonhealthbox.push_back(bx);
		simonhealthframe.push_back(0);
	}
	for (int i = 0; i < maxhealth; i++)
	{
		float boxX = x - maxhealth/2 * getWidth() - getWidth() / 2;
		boxX = x + i * getWidth();
		float boxY = y;
		Box bx(boxX, boxY, getWidth(), getHeight());
		bosshealthbox.push_back(bx);
		bosshealthframe.push_back(0);
	}

}

void chealthbar::update(int _simonhealth, int _bosshealth)
{
	if (_simonhealth != simonhealth)
	{
		simonhealth = _simonhealth;
		emptysimonhealth = maxhealth - _simonhealth;
		for (int i = 0; i < simonhealthframe.size(); i++)
		{
			if (i <= _simonhealth)
				simonhealthframe.at(i) = 0;
			else 
			if (i > _simonhealth)
				simonhealthframe.at(i) = 1;
		}
	}

	if (_bosshealth != bosshealth)
	{
		bosshealth = _bosshealth;
		emptybosshealth = maxhealth - _bosshealth;
		for (int i = 0; i < bosshealthframe.size(); i++)
		{
			if (i <= _bosshealth)
				bosshealthframe.at(i) = 2;
			else
			if (i > _bosshealth)
				bosshealthframe.at(i) = 1;
		}
	}
}

void chealthbar::render(int delta)
{
	for (int i = 0; i < simonhealthbox.size(); i++)
	{
		_draw(simonhealthbox.at(i), simonhealthframe.at(i));
	}
	for (int i = 0; i < bosshealthbox.size(); i++)
	{
		_draw(bosshealthbox.at(i), bosshealthframe.at(i));
	}
}

void chealthbar::_draw(Box bx, int tile)
{
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	RECT		srcRect;
	srcRect.left = (tile % getColumns()) * bx.w;
	srcRect.top = (tile / getColumns()) * bx.h;
	srcRect.right = srcRect.left + bx.w;
	srcRect.bottom = srcRect.top + bx.h;
	position.x = bx.x - bx.w / 2;
	position.y = bx.y - bx.h / 2;
	SpriteHandler->Draw(
		this->_Texture,
		&srcRect,
		&center,
		&position,
		D3DCOLOR_ARGB(alphablend, Color.getR(), Color.getG(), Color.getB()));
}
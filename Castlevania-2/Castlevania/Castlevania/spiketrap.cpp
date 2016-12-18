#include "spiketrap.h"

void cspiketrap::load(char* filepath)
{
	CSprite::load(filepath, 1, 2);
	_Status.push_back(1);
	_Speed = 2;
}

int cspiketrap::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void cspiketrap::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(1);
}

void cspiketrap::setStatus(int id, int stt)
{
	int position = findVectorPosition(id);
	_Status.at(position) = stt;
}

void cspiketrap::update(int delta, int id)
{
	int position = findVectorPosition(id);
	switch (_Status.at(position))
	{
	case 1:
		_Box.at(position).vy = - _Speed;
		_Box.at(position).h += _Speed;
		break;
	case 2:
		_Box.at(position).vy = _Speed;
		_Box.at(position).h -= _Speed;
		if (_Box.at(position).h <= 16)
		{
			_Status.at(position) = 1;
			//_Box.at(position).h = 16;
		}
		break;
	}
	_Box.at(position).y += _Box.at(position).vy;
}

int cspiketrap::render(int delta, int id)
{
	int vectorPosition = findVectorPosition(id);
	if (vectorPosition)
	{
		D3DXVECTOR2 TransformPosition;
		int fulltiles = _Box.at(vectorPosition).h / getHeight();
		float remainpart = _Box.at(vectorPosition).h - (fulltiles * getHeight());
		TransformPosition = cmr.GetPointTransform(_Box.at(vectorPosition).x + _Box.at(vectorPosition).w / 2,
			_Box.at(vectorPosition).y + getHeight() / 2);
		_draw(1, TransformPosition.x, TransformPosition.y, getHeight());
		for (int i = 1; i < fulltiles; i++)
		{
			int x = _Box.at(vectorPosition).x;
			int y = _Box.at(vectorPosition).y + i * getHeight();
			TransformPosition = cmr.GetPointTransform(x + _Box.at(vectorPosition).w / 2,
				y + getHeight() / 2);
			_draw(0, TransformPosition.x, TransformPosition.y, getHeight());
		}
		int x = _Box.at(vectorPosition).x;
		int y = _Box.at(vectorPosition).y + (fulltiles)* getHeight();
		TransformPosition = cmr.GetPointTransform(x + _Box.at(vectorPosition).w / 2,
			y + getHeight() / 2);
		_draw(0, TransformPosition.x, TransformPosition.y, remainpart);
		return 1;
	}
	return 0;
}

void cspiketrap::_draw(int tile, float x, float y, float height)
{
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	RECT		srcRect;
	srcRect.left = (tile % getColumns()) * getWidth();
	srcRect.right = srcRect.left + getWidth();
	srcRect.bottom = (tile / getColumns()) * getHeight();
	srcRect.top = srcRect.bottom + height;
	position.x = x - getWidth() / 2;
	position.y = y - getHeight() / 2;
	SpriteHandler->Draw(
		this->_Texture,
		&srcRect,
		&center,
		&position,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}
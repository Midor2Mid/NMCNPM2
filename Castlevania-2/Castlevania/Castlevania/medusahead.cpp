#include "medusahead.h"


void CMedusahead::load(char* filename)
{
	CSprite::load(filename, 2, 1);
	_AnimationTick.push_back(0);
	_Status.push_back(0);
	_Currentframe.push_back(0);
	_Startframe.push_back(0);
	_Lastframe.push_back(0);
}

void CMedusahead::ClearAll()
{
	CSprite::ClearAll();
	_Status.clear();
	_Startframe.clear();
	_Lastframe.clear();
	_AnimationTick.clear();
	_Currentframe.clear();
}

void CMedusahead::animate(int animationdelay, int startframe, int lastframe, int id)
{
	int pos = findVectorPosition(id);
	_Animationdelay = animationdelay;
	_Startframe.at(pos) = startframe;
	_Lastframe.at(pos) = lastframe;
}

void CMedusahead::animate(int delta, int _id)
{
	int pos = findVectorPosition(_id);
	if (_AnimationTick.at(pos) >= _Animationdelay)
	{
		_AnimationTick.at(pos) = delta - _Animationdelay;
		if (_Currentframe.at(pos) < _Startframe.at(pos))
			_Currentframe.at(pos) = _Startframe.at(pos) - 1;
		if (++_Currentframe.at(pos) > _Lastframe.at(pos))
		{
			_Currentframe.at(pos) = _Startframe.at(pos);
		}
	}
	else
	{
		_AnimationTick.at(pos) += delta;
	}
}

void CMedusahead::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(0);
	_Currentframe.push_back(0);
	_Startframe.push_back(0);
	_Lastframe.push_back(0);
	_AnimationTick.push_back(0);
}

CMedusahead::CMedusahead()
{
}

CMedusahead::~CMedusahead()
{
}

int CMedusahead::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void CMedusahead::moveLikeJagger(int delta, int id)
{
	int pos = findVectorPosition(id);
	_Box.at(pos).vx = delta * 0.12;
	float nextX = _Box.at(pos).vx + _Box.at(pos).x;
	float nextY = 6 * sin(nextX / 10);
	_Box.at(pos).vy = nextY;
	_Box.at(pos).x += _Box.at(pos).vx;
	_Box.at(pos).y += _Box.at(pos).vy;
}

void CMedusahead::update(int delta, int id)
{
	int position = findVectorPosition(id);

	if (_Status.at(position) != 0 && _Status.at(position) != 100)
	{
		if (cmr.pos.x + SCREENWIDTH + 150 < getX(id) || cmr.pos.x - 150 > getX(id))
		{
			_Status.at(position) = 100;
		}
	}

	switch (_Status.at(position))
	{
	case 0:
		if (cmr.pos.x + SCREENWIDTH > _Box.at(position).x && cmr.pos.x < _Box.at(position).x + _Box.at(position).w && cmr.pos.y > _Box.at(position).y && cmr.pos.y - SCREENHEIGHT < _Box.at(position).y + _Box.at(position).h)
			_Status.at(position) = 1;
		break;
	case 1:
		animate(30, 0, 1, id);
		if (CSprite::isFlip(id))
		{
			moveLikeJagger(delta, id);
		}
		else
		{
			moveLikeJagger(-delta, id);
		}
		break;
	}
}

int CMedusahead::render(int delta, int _id)
{
	animate(delta, _id);
	int temp = findVectorPosition(_id);
	if (temp)
	{
		D3DXVECTOR2 TransformPosition;
		switch (_Camera.at(temp))
		{
		case 0:
			TransformPosition = cmr.GetPointTransform(_Box.at(temp).x + _Box.at(temp).w / 2, _Box.at(temp).y + _Box.at(temp).h / 2);
			break;
		case 1:
			TransformPosition = cmr2.GetPointTransform(_Box.at(temp).x + _Box.at(temp).w / 2, _Box.at(temp).y + _Box.at(temp).h / 2);
			break;
		}
		if (_Flip.at(temp))
			flip(delta, TransformPosition.x, TransformPosition.y, temp);
		else
			draw(delta, TransformPosition.x, TransformPosition.y, temp);
		return 1;
	}
	return 0;
}

void CMedusahead::draw(int delta, float x, float y, int pos)
{
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	RECT		srcRect;
	srcRect.left = (_Currentframe.at(pos) % getColumns()) * getWidth();
	srcRect.top = (_Currentframe.at(pos) / getColumns()) * getHeight();
	srcRect.right = srcRect.left + getWidth();
	srcRect.bottom = srcRect.top + getHeight();
	position.x = x - getWidth() / 2;
	position.y = y - getHeight() / 2;
	SpriteHandler->Draw(
		this->_Texture,
		&srcRect,
		&center,
		&position,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMedusahead::flip(int delta, float x, float y, int pos)
{
	D3DXMATRIX		oldMt;
	SpriteHandler->GetTransform(&oldMt);
	D3DXMATRIX		newMt;
	D3DXVECTOR2		center = D3DXVECTOR2((x + getWidth() / 2), (y + getHeight() / 2));
	D3DXVECTOR2		rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX		finalMt = newMt * oldMt;
	SpriteHandler->SetTransform(&finalMt);

	float temp = x;						// Luu tru vi tri thuc te
	x += getWidth();
	this->draw(delta, x, y, pos);
	SpriteHandler->SetTransform(&oldMt);			// Tra lai gia tri ma tran ban dau neu khong thi sprite se bi lat lien tuc
}
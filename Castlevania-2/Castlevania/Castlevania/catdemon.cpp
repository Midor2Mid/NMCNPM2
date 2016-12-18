#include "catdemon.h"

void CCat::load(char* filepath)
{
	CSprite::load(filepath, 4, 1);
	_AnimationTick.push_back(0);
	_Status.push_back(0);
	_Currentframe.push_back(0);
	_Startframe.push_back(0);
	_Lastframe.push_back(0);
}

void CCat::addNewObject(int id, float x, float y,float width, float height, int flip)
{
	CSprite::addNewObject(id, x, y, width, height, flip);
	_Status.push_back(0); 
	_Currentframe.push_back(0);
	_Startframe.push_back(0);
	_Lastframe.push_back(0);
	_AnimationTick.push_back(0);
}

void CCat::ClearAll()
{
	CSprite::ClearAll();
	_Status.clear();
	_Startframe.clear();
	_Lastframe.clear();
	_AnimationTick.clear();
	_Currentframe.clear();
}

void CCat::animate(int animationdelay, int startframe, int lastframe, int id)
{
	int pos = findVectorPosition(id);
	_Animationdelay = animationdelay;
	_Startframe.at(pos) = startframe;
	_Lastframe.at(pos) = lastframe;
}

void CCat::animate(int delta, int _id)
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

void CCat::setStatus(int status, int id)
{
	_Status.at(findVectorPosition(id)) = status;
}

int CCat::isActive(int id)
{
	return _Status.at(findVectorPosition(id));
}

void CCat::update(int delta, int id)
{
	int position = findVectorPosition(id);
	if (_Status.at(position) != 0)
	{
		if (cmr.pos.x + SCREENWIDTH + 500 < getX(id) || cmr.pos.x - 500 > getX(id))
		{
			_Status.at(position) = 100;
		}
	}

	switch (_Status.at(position))
	{
	case 0:
		if (cmr.pos.x + SCREENWIDTH > getX(id) && cmr.pos.x < getX(id))
			_Status.at(position) = 1;
		break;
	case 1:
		animate(20, 1, 3, id); 
		_Box.at(position).vy = 0;
		if (CSprite::isFlip(id))
		{
			_Box.at(position).vx = delta * 0.25;
		}
		else
		{
			_Box.at(position).vx = -delta * 0.25;
		}
		break;
	case 2:
		animate(50, 3, 3, id);
		if (CSprite::isFlip(id))
		{
			  _Box.at(position).vx = delta * 0.25;
		}
		else
		{
			  _Box.at(position).vx = -delta * 0.25;
		}
		_Box.at(position).vy -= 0.2;
		break;
	}
	_Box.at(position).x += _Box.at(position).vx;
	_Box.at(position).y += _Box.at(position).vy;
}

int CCat::render(int delta, int _id)
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

void CCat::draw(int delta, float x, float y, int pos)
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

void CCat::flip(int delta, float x, float y, int pos)
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
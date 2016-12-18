#include "bossbat.h"

void CBossbat::load(char*filepath)
{
	CSprite::load(filepath, 3, 1);
	CSprite::animate(true);
	CSprite::animate(50, 0,0);
	bossstate = 0;
	_Vx = 0;
	_Vy = 0;
	_Dx = 0;
	_Dy = 0;
	_WaitingTime = 0;
	_CurrentWaitingTime = 0;
	srand(time_t(NULL));
	_Status = 0;
	health = 19;
	invulnerable = 0; 
	invulnerablecounttime = 0;
	invulnerablecount = 0;
	invulnerableCountInvert = 0;
	_StopUpdate = false;
	//_StopUpdate = 0;
}

int CBossbat::getHealth()
{

	return health;
}

void CBossbat::setStopUpdate(int stop)
{
	_StopUpdate = stop;
}

void CBossbat::moveX(int vx)
{
	_Vx = vx;
}
void CBossbat::moveY(int vy)
{
	_Vy = vy;
}

void CBossbat::getObject(Box bx)
{
	_DestinationX = _Box.at(0).x + _Box.at(0).w / 2 - bx.x;
	_DestinationY = _Box.at(0).y + _Box.at(0).h / 2 - bx.y;
}

void CBossbat::setStatus(int stt, int id)
{
	_Status = stt;
}

int CBossbat::getStatus()
{
	return _Status;
}

int CBossbat::isActive(int id)
{
	return _Status;
}

void CBossbat::update(int delta, Box bx, int id)
{
	if (!_StopUpdate)
	{
		int vectorPosition = findVectorPosition(id);
		switch (_Status)
		{
		case 0:
			if (cmr.pos.x + SCREENWIDTH > _Box.at(vectorPosition).x &&
				cmr.pos.x < _Box.at(vectorPosition).x + _Box.at(vectorPosition).w &&
				cmr.pos.y > _Box.at(vectorPosition).y &&
				cmr.pos.y - SCREENHEIGHT < _Box.at(vectorPosition).y + _Box.at(vectorPosition).h)
				_Status = 1;
			break;
		case 1:
			break;
		case 2:
#pragma region
			float currentRenderX;
			switch (bossstate)
			{
			case 0:
				//khoi tao toa do den va tim a
				_DestinationX = bx.x;
				_DestinationY = bx.y;
				_CurrentDestinationX = getX(id) - _DestinationX;
				_CurrentDestinationY = getY(id) - _DestinationY;
				_MovingSpeed = -_CurrentDestinationX / 80;
				a = _CurrentDestinationY / (_CurrentDestinationX * _CurrentDestinationX);
				bossstate = 1;
				//animate(50, 1, 2);
				break;
			case 1:
				//Bat dau tan cong
				animate(20, 1, 2);
				currentRenderX = getX(id);
				currentRenderX += _MovingSpeed;
				virtualx = currentRenderX - _DestinationX;
				setPosition(currentRenderX, virtualx * virtualx * a + _DestinationY, id);

				if (getY(id) <= _DestinationY + 20)
				if (_MovingSpeed < 0)
				{
					if (getX(id) < _DestinationX)
					{
						bossstate = 2;
						int Xposition = rand() % 3;
						switch (Xposition)
						{
						case 0:
							_ReturnPositionX = cmr.pos.x + SCREENWIDTH / 10;
							break;
						case 1:
							_ReturnPositionX = cmr.pos.x + SCREENWIDTH / 2;
							break;
						case 2:
							_ReturnPositionX = cmr.pos.x + 8 * SCREENWIDTH / 10;
							break;
						}
						int Yposition = rand() % 2;
						switch (Yposition)
						{
						case 0:
							_ReturnPositionY = cmr.pos.y - 2 * SCREENHEIGHT / 4;
							break;
						case 1:
							_ReturnPositionY = cmr.pos.y - 3 * SCREENHEIGHT / 5;
							break;
						}
						_MovingSpeed = (_ReturnPositionX - getX(id)) / 80;
						a = (getY(id) - _ReturnPositionY) / (getX(id) - _ReturnPositionX);
					}
				}
				else
				{
					if (getX(id) > _DestinationX)
					{
						bossstate = 2;
						int Xposition = rand() % 3;
						switch (Xposition)
						{
						case 0:
							_ReturnPositionX = cmr.pos.x + SCREENWIDTH / 10;
							break;
						case 1:
							_ReturnPositionX = cmr.pos.x + SCREENWIDTH / 2;
							break;
						case 2:
							_ReturnPositionX = cmr.pos.x + 8 * SCREENWIDTH / 10;
							break;
						}
						int Yposition = rand() % 2;
						switch (Yposition)
						{
						case 0:
							_ReturnPositionY = cmr.pos.y - 2 * SCREENHEIGHT / 4;
							break;
						case 1:
							_ReturnPositionY = cmr.pos.y - 3 * SCREENHEIGHT / 5;
							break;
						}
						_MovingSpeed = (_ReturnPositionX - getX(id)) / 80;
						a = (getY(id) - _ReturnPositionY) / (getX(id) - _ReturnPositionX);
					}
				}
				break;
			case 2:
				currentRenderX = getX(id);
				currentRenderX += _MovingSpeed;
				virtualx = currentRenderX - _ReturnPositionX;
				setPosition(currentRenderX, virtualx * a + _ReturnPositionY, id);
				if (getY(id) > _ReturnPositionY)
				{
					animate(50, 1, 2);
					bossstate = 3;
					_WaitingTime = rand() % 2000;
				}
				//Bat tro ve vi tri bat ki
				break;
			case 3:
				if (_CurrentWaitingTime > _WaitingTime)
				{
					bossstate = 0;
					_CurrentWaitingTime = 0;
					a = 0;
					_MovingSpeed = 0;
					virtualx = 0;
				}
				else
					_CurrentWaitingTime += delta;
				break;
			}
#pragma endregion boss hoat dong
			break;
		case 3:
#pragma region

#pragma endregion	Invisible Boss
			break;
		}
	}
	_StopUpdate = false;
}

int CBossbat::render(int delta, int id)
{
	if (invulnerable)
	{
		if (!invulnerableCountInvert)
		{
			invulnerablecount += 20;
		}
		else
		{
			invulnerablecount -= 20;
		}

		if (invulnerablecount > 255 && !invulnerableCountInvert)
		{
			invulnerableCountInvert = true;
			invulnerablecounttime++;
			invulnerablecount = 255;
		}

		if (invulnerablecount < 0 && invulnerableCountInvert)
		{
			invulnerablecounttime++;
			invulnerableCountInvert = false;
			invulnerablecount = 0;
		}
		Color.setA(invulnerablecount);
		if (invulnerablecounttime == 3)
		{
			invulnerablecounttime = 0;
			invulnerable = false;
			invulnerablecount = 0;
			invulnerablecounttime = 0;
			Color.setA(255);
		}
	}
	else
		Color.setA(255);
	return CSprite::render(delta, id);
}
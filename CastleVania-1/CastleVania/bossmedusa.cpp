#include "bossmedusa.h"

void CBossmedusa::load(char* filepath)
{
	CSprite::load(filepath, 5, 1);
	animate(true);
	animate(500, 4, 4, 1);
	_Status = 0;
	health = 19;
	invertmove = false;
	maximumWaitingTime = 0;
	_StopUpdate = false;
}

void CBossmedusa::setStopUpdate(int stop)
{
	_StopUpdate = stop;
}
void CBossmedusa::update(int delta, Box bx, int id)
{
	if (!_StopUpdate)
	{

		if (_Status != 0 && _Status != 1)
		if (health < 8)
		{
			animate(50, 2, 3, 1);
		}
		else
		{
			animate(60, 0, 1, 1);
		}

		int vectorPosition = findVectorPosition(id);
		int currentTilePos;
		switch (_Status)
		{
		case 0:
			animate(0, 4, 4, 1);
			if (cmr.pos.x + SCREENWIDTH > _Box.at(vectorPosition).x &&
				cmr.pos.x < _Box.at(vectorPosition).x + _Box.at(vectorPosition).w &&
				cmr.pos.y > _Box.at(vectorPosition).y &&
				cmr.pos.y - SCREENHEIGHT < _Box.at(vectorPosition).y + _Box.at(vectorPosition).h)
			{
				_BalanceY = _Box.at(vectorPosition).y;
				_Status = 1;
			}
			break;
		case 1:
			break;
		case 2:
			srand(time(NULL));
			if (bx.x - _Box.at(vectorPosition).x > 0)
				_Status = 4;
			else
				_Status = 3;
			currentTilePos = (_Box.at(vectorPosition).x - cmr.pos.x) / (SCREENWIDTH / 5);
			int result;
			if (_Status == 4)
			{
				int temp = currentTilePos + 1;
				result = rand() % 5;
				result += temp;
				_DestinationXPosition = (int)(result * (SCREENWIDTH / 5) + cmr.pos.x - getWidth());
				if (_DestinationXPosition > cmr.pos.x + SCREENWIDTH)
					_DestinationXPosition = cmr.pos.x + SCREENWIDTH - getWidth();
			}
			else
			if (_Status == 3)
			{
				int temp = currentTilePos - 1;
				if (temp == 0)
					temp = 1;
				result = rand() % temp;
				_DestinationXPosition = (int)(result * (SCREENWIDTH / 5) + cmr.pos.x);
				if (_DestinationXPosition < cmr.pos.x)
					_DestinationXPosition = cmr.pos.x;
			}
			break;
		case 3:
			moveLikeJagger(-delta, id);
			if (_Box.at(vectorPosition).x < _DestinationXPosition)
			{
				_Status = 5;
			}
			break;
		case 4:
			moveLikeJagger(delta, id);
			if (_Box.at(vectorPosition).x > _DestinationXPosition)
			{
				_Status = 5;
			}
			break;
		case 5:
			_Waitingtime += delta;
			maximumWaitingTime = rand() % 500;
			maximumWaitingTime = maximumWaitingTime + 500;
			if (_Waitingtime > maximumWaitingTime)
			{
				if (_Box.at(vectorPosition).y > _BalanceY + 100 || _Box.at(vectorPosition).y < _BalanceY - 200)
					_Status = 6;
				else
				{
					int r = rand() % 5;
					if (r == 1 || r == 2)
						_Status = 6;
					else
						_Status = 2;
				}
				_Waitingtime = 0;
			}
			//standing
			break;
		case 6:
			if (_Box.at(vectorPosition).x - bx.x > 0)
			{
				_DestinationX = cmr.pos.x + 30;
			}
			else
			{
				_DestinationX = cmr.pos.x + SCREENWIDTH - 30;
			}
			_DestinationY = _BalanceY;
			_CurrentDestinationX = getX(id) - _DestinationX;
			_CurrentDestinationY = getY(id) - _DestinationY;
			_MovingSpeed = -_CurrentDestinationX / 80;
			a = _CurrentDestinationY / (_CurrentDestinationX * _CurrentDestinationX);
			_Status = 7;
			break;
		case 7:
			float currentRenderX;
			//animate(20, 1, 2);
			currentRenderX = getX(id);
			currentRenderX += _MovingSpeed;
			virtualx = currentRenderX - _DestinationX;
			setPosition(currentRenderX, virtualx * virtualx * a + _DestinationY, id);

			if (getY(id) <= _DestinationY + 20)
			if (_MovingSpeed > 0)
			{
				if (getX(id) < _DestinationX)
				{
					_Status = 5;
				}
			}
			else
			if (getX(id) > _DestinationX)
			{
				_Status = 5;
			}
			break;
		}
	}
	_StopUpdate = false;
}

void CBossmedusa::setStatus(int stt, int id)
{
	_Status = stt;
}

int CBossmedusa::getStatus()
{
	return _Status;
}

int CBossmedusa::getHealth()
{
	return health;
}

int CBossmedusa::isActive(int id)
{
	return _Status;
}

void CBossmedusa::moveLikeJagger(int delta, int id)
{
	int pos = findVectorPosition(id);
	_Box.at(pos).vx = delta * 0.12;
	float nextX = _Box.at(pos).vx + _Box.at(pos).x;
	float nextY = 4* sin(nextX / 15);
	_Box.at(pos).vy = nextY;
	_Box.at(pos).x += _Box.at(pos).vx;
	_Box.at(pos).y += _Box.at(pos).vy;
}

int CBossmedusa::render(int delta, int id)
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
	return CSprite::render(delta, id);
}
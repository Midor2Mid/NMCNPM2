#include "simon.h"
#include "loadfile.h"

#pragma region

BoxCollision::BoxCollision()
{
}

BoxCollision::BoxCollision(int type, int dimension, int id, float x, float y)
{
	_Type = type;
	_Dimension = dimension;
	_Id = id;
	_X = x;
	_Y = y;
}

BoxCollision::BoxCollision(int type, int dimension, int id, float x, float y, float w, float h)
{
	_Type = type;
	_Dimension = dimension;
	_Id = id;
	_X = x;
	_Y = y;
	_W = w;
	_H = h;
}

BoxCollision::BoxCollision(int type, int dimension, int id)
{
	_Type = type;
	_Dimension = dimension;
	_Id = id;
	_X = 0;
	_Y = 0;
}

int BoxCollision::getDimension()
{
	return _Dimension;
}

int BoxCollision::getType()
{
	return _Type;
}

int BoxCollision::getId()
{
	return _Id;
}

float BoxCollision::getWidth()
{
	return _W;
}

float BoxCollision::getHeight()
{
	return _H;
}

void BoxCollision::setId(int id)
{
	_Id = id;
}

void BoxCollision::setType(int type)
{
	_Type = type;
}

void BoxCollision::setDimension(int dimension)
{
	_Dimension = dimension;
}

void BoxCollision::setXY(float x, float y)
{
	_X = x;
	_Y = y;
}

float BoxCollision::getX()
{
	return _X;
}

float BoxCollision::getY()
{
	return _Y;
}

#pragma endregion class BoxCollision

CSimon::CSimon()
{
	_Vx = 0;
	_Vy = 0;
	_FightInitialize = false;
	_JumpInitialize = false;
	_Status = 0;
	_Jump = false;
	_LadderDirection = 0;
	_FlagUp = 0;
	_FlagDown = 0;
	_resetJump = false;
	_SaveVx = 0;
	isStand = true;
	_OnJumpUpCollision = false;
	_JumpAction = 0; 
	goInCastle = false;
	
	CastleGateWidth = 0;
	CastleGateX = 0;
	startGoinCastle = false;
	nextlevel = false; 
	stepOnLadderHeight = 0;
	isSatOnGround = 0;
	_KnockBack = false;
	_StoptimeWaitingLimit = 3000; 
	_StoptimeWaitingCount = 0;
	_StopTime = false;
	_OnFlyingObject = 0;
}

CSimon::~CSimon()
{
	_OnLadder = 0;
}

bool CSimon::isStopTime()
{
	return _StopTime;
}

void CSimon::resetCharacter()
{
	_KnockBack = false;
	_StoptimeWaitingLimit = 3000;
	_StoptimeWaitingCount = 0;
	_StopTime = false;
	PrimaryWeapon = 0;
	SecondaryWeapon = 0 ;
	HealthPoint = 19;
	SecondaryWeaponUsePoint = 10;
	_OnLadder = 0;
	stepOnLadder = 0;
}

void CSimon::resetCharacterForNextLevel()
{
	_KnockBack = false;
	_StoptimeWaitingLimit = 3000; 
	_StoptimeWaitingCount = 0;
	_StopTime = false;
	SecondaryWeaponUsePoint = 10;
	HealthPoint = 19;
}

void CSimon::CreateCheckPoint()
{
	checkpointX = getX();
	checkpointY = getY();
}

void CSimon::ResetToCheckPoint()
{
	setPosition(checkpointX, checkpointY);
}

void CSimon::load(char* filename, int columns, int rows)
{
	DeathSprite.load("resource/image/simondeath.png", 1, 1);
	CSprite::load(filename, columns, rows);
	animate(true);
	setPosition(0, 0);
	_Box.at(0).x = getX() - 14;
	_Box.at(0).w = 28;
	ObjectCollided.clear();
	animate(0, 0, 0);
	_TempWidth = getWidth();
	MorningStar.load("resource/image/morningstar.png", 4, 3); 
	MorningStar.animate(false); 
	invulnerable			= false;
	invulnerablecount		= 0;
	invulnerablecounttime	= 0;
	invulnerableCountInvert = false;
	HealthPoint = 19;
	waitingtime = 0;
	death	= false;
	isReset = false;
	
	vector<string> weaponlink = loadLink("resource/weapon.txt");;
	//load cac vu khi
	dagger.load((char*)weaponlink.at(0).c_str(), 1, 1);
	dagger.setType(1);
	holywater.load((char*)weaponlink.at(1).c_str(), 3, 1);
	holywater.setType(2);
	axe.load((char*)weaponlink.at(2).c_str(), 4, 1); 
	axe.setType(3);
	boomerang.load((char*)weaponlink.at(3).c_str(), 3, 1);
	boomerang.setType(4);
	SecondaryWeaponUsePoint = 10;
	secondaryweaponfight = 0;
	SecondaryWeaponLimit = 1;
	SecondaryWeapon = 0;
	currentWeaponSorP = 0;
	QueueFight = 0;
	flyingObjectVx = 0;

	_usingwhipsound = LoadSound("resource/sound/usingwhip.wav");
}

int CSimon::getStatus()
{
	return _Status;
} 

void CSimon::setflyingObjectVx(float vx)
{
	flyingObjectVx = vx;
}

float CSimon::getflyingObjectVx()
{
	return flyingObjectVx;
}

void CSimon::setStatus(int stt)
{
	_Status = stt;
}

void CSimon::stand(int delta)
{
	
	if (!_KnockBack)
	{
		_Box.at(0).vy = 0; 
		_Box.at(0).vx = 0;
	}

	if (isSatOnGround)
		setCurrentFrame(4);
	else
		setCurrentFrame(0);
	animate(false);
}		//0

void CSimon::moveLeft(int delta)
{
	animate(true);
	CSprite::animate(30, 0, 3);
	_Box.at(0).vx = -delta * 0.15;
	_Status = 0;
}		//1

void CSimon::moveRight(int delta)
{
	animate(true);
	CSprite::animate(30, 0, 3);
	_Box.at(0).vx = delta * 0.15;
	_Status = 0;
}		//2

bool CSimon::CheckHorizontalCollision(Box bx, BoxCollision bx2)
{
	if (bx.x + bx.w < bx2.getX() + 5 || bx.x > bx2.getX() + bx2.getWidth() - 5)
		return false;
	return true;
}

bool CSimon::CheckVerticalCollision(Box bx, BoxCollision bx2)
{
	if (bx.y > bx2.getY() + 5)
		return true;
	return false;
}

int CSimon::GetStepOnLadderDirection()
{
	return stepOnLadderDirection;
}

void CSimon::endJump()
{
	_Box.at(0).collisionTime = 0;
	_JumpInitialize = false;
	_SaveVx = 0;
	if (!isStand)
	{
			_Box.at(0).vy -= 18;
			_Box.at(0).h += 18;
			SwiftToStand = true;
			isStand = true;
	}
}

int CSimon::JumpStage(int delta)
{
	if (!_JumpInitialize)
	{
#pragma region
		animate(true);
		_AccelerateY = 0;
		_Box.at(0).vy = 5.5;
		_JumpInitialize = true;
		_resetJump = false;
		_OnJumpUpCollision = false;

		//khi simon nhay ngoi
		_Box.at(0).vy += 18;
		_Box.at(0).h -= 18;
		SwiftToSit = true;
		isStand = false;
		SwiftToStand = false;
		_SaveVx = 0;
		if(Key_Down(DIK_A))
		{
			_SaveVx = -0.15*delta;
		}
		else
		if (Key_Down(DIK_D))
		{
			_SaveVx = 0.15*delta;
		}
#pragma endregion khoi tao nhay
	}
	else
	{
		_Box.at(0).vy += _AccelerateY;
		_AccelerateY -= 0.05f;

		if (!isStand)
		{
			if (_JumpAction == 0)
			{
				if (_Box.at(0).vy <= -1)
				{
					if(!isFight)
						animate(30, 0, 0);
					_Box.at(0).vy -= 18;
					_Box.at(0).h += 18;
					SwiftToStand = true;
					isStand = true;
				}
			}
			if (_JumpAction == 1)
			{
				if (!isFight)
					animate(30, 0, 0);
				_Box.at(0).vy -= 18;
				_Box.at(0).h += 18;
				SwiftToStand = true;
				isStand = true;
			}
		}

		if (_Box.at(0).vy <= 0)
		{
			if (!_resetJump)
			{
				_AccelerateY = 0;
				_resetJump = true;
			}
		}

		if (_SaveVx != 0)
		{
			if (ObjectCollided.size() == 0)
			{
				sideblocked = 0;
				_Box.at(0).vx = _SaveVx;
			}
		}

		if (_OnJumpUpCollision)
		{
			if (ObjectCollided.size() == 0)
				_OnJumpUpCollision = false;
		}

		if (ObjectCollided.size() > 0)
		{
			for (int i = 0; i < ObjectCollided.size(); i++)
			{
				if (ObjectCollided.at(i).getDimension() == 5)
				{
					_Box.at(0).vx = 0;
					if (_Box.at(0).vy >= 0)
						_OnJumpUpCollision = true;
					if (!_OnJumpUpCollision &&_Box.at(0).vy <= 0)
					{
						if (CheckHorizontalCollision(_Box.at(0), ObjectCollided.at(i)) && CheckVerticalCollision(_Box.at(0), ObjectCollided.at(i)))
						{
							_Box.at(0).collisionTime = 0;
							_Box.at(0).y = ObjectCollided.at(i).getY() + ObjectCollided.at(i).getHeight();
							_JumpInitialize = false;
							_SaveVx = 0;
							if (!isStand)
							{
								if (_JumpAction == 0)
								{
									if (_Box.at(0).vy <= 0)
									{
										_Box.at(0).vy -= 18;
										_Box.at(0).h += 18;
										SwiftToStand = true;
										isStand = true;
									}
								}
							}
							return 1;
						}
					}
				}

				if (ObjectCollided.at(i).getDimension() == 4)
				{
					_OnJumpUpCollision = true;
					_Box.at(0).collisionTime = 1;
				}

				if (ObjectCollided.at(i).getDimension() == 1)
				{
					_Box.at(0).vx = 0;
					//sideblocked = 1;
				}


				if (ObjectCollided.at(i).getDimension() == 2)
				{

				_Box.at(0).vx = 0;
				}
				
				if (ObjectCollided.at(i).getDimension() == 3)
				{
					if (CheckHorizontalCollision(_Box.at(0), ObjectCollided.at(i)) && CheckVerticalCollision(_Box.at(0), ObjectCollided.at(i)))
					{
						_Box.at(0).y = ObjectCollided.at(i).getY() + ObjectCollided.at(i).getHeight();
						_Box.at(0).collisionTime = 0;
						_JumpInitialize = false;
						_SaveVx = 0;
						if (!isStand)
						{
							if (_JumpAction == 0)
							{
								if (_Box.at(0).vy <= 0)
								{
									_Box.at(0).vy -= 18;
									_Box.at(0).h += 18;
									SwiftToStand = true;
									isStand = true;
								}
							}
						}
						return 1;
					}
				}
			}
		}
	}
	return 0;
}		//3

void CSimon::useWeapon()
{
	_Status = 8;
}		//8

int CSimon::knockBack()
{
	setCurrentFrame(8);
	if (!_JumpInitialize)
	{
		isFight = false;
		_Action = 1;
		animate(true);
		_AccelerateY = 0;
		_Box.at(0).vy = 5.5;
		_JumpInitialize = true;
		_resetJump = false;
		_OnJumpUpCollision = false;
		if(isFlip())
			_Box.at(0).vx = -1.5;
		else
			_Box.at(0).vx = 1.5;

		if (isFight)
			isFight = false;
	}
	else
	{
		
		_Box.at(0).vy += _AccelerateY;
		_AccelerateY -= 0.06f;
		if (_Box.at(0).vy <= 0)
		{
			if (!_resetJump)
			{
				_AccelerateY = 0;
				_resetJump = true;
			}
		}

		if (_OnJumpUpCollision)
		{
			if (ObjectCollided.size() == 0)
				_OnJumpUpCollision = false;
		}
		if (_Box.at(0).vx==0)
		if (ObjectCollided.size() == 0)
		{
			if (isFlip())
				_Box.at(0).vx = -1.5;
			else
				_Box.at(0).vx = 1.5;
		}

		if (ObjectCollided.size() > 0)
		{
			for (int i = 0; i < ObjectCollided.size(); i++)
			{
				if (ObjectCollided.at(i).getDimension() == 5)
				{
					_Box.at(0).vx = 0;
					if (_Box.at(0).vy >= 0)
						_OnJumpUpCollision = true;
					if (!_OnJumpUpCollision &&_Box.at(0).vy <= 0)
					{
						if (CheckHorizontalCollision(_Box.at(0), ObjectCollided.at(i)) && CheckVerticalCollision(_Box.at(0), ObjectCollided.at(i)))
						{
							if (isFlip())
								setFlip(false);
							else
								setFlip(true);
							_Box.at(0).collisionTime = 0;
							_Box.at(0).y = ObjectCollided.at(i).getY() + ObjectCollided.at(i).getHeight();
							_JumpInitialize = false;
							_KnockBack = false;
							_Box.at(0).vx = 0;
							_Action = 1;
							invulnerable = true;
							return 1;
						}
					}
				}

				if (ObjectCollided.at(i).getDimension() == 4)
				{
					_OnJumpUpCollision = true;
					_Box.at(0).collisionTime = 1;
					_Box.at(0).vx = 0;
				}
				
				if (ObjectCollided.at(i).getDimension() == 1)
				{
					_Box.at(0).vx = 0;
				}


				if (ObjectCollided.at(i).getDimension() == 2)
				{
					_Box.at(0).vx = 0;
				}

				if (ObjectCollided.at(i).getDimension() == 3)
				{
				
					if (CheckHorizontalCollision(_Box.at(0), ObjectCollided.at(i)) && CheckVerticalCollision(_Box.at(0), ObjectCollided.at(i)))
					{
						if (isFlip())
							setFlip(false);
						else
							setFlip(true);
						_Box.at(0).y = ObjectCollided.at(i).getY() + ObjectCollided.at(i).getHeight();
						_Box.at(0).collisionTime = 0;
						_JumpInitialize = false;
						_KnockBack = false;
						_Box.at(0).vx = 0;
						_Action = 1;
						invulnerable = true;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}		//9

int CSimon::isJump()
{
	return _Jump;
}

void CSimon::jump()
{
	if (_Action == 1 && !isSatOnGround&&!_OnLadder&&!_KnockBack)
	{
		animate(30, 4, 4);
 		_Action = 2;
		_JumpAction = 0;
	}
}

void CSimon::fight(int secondorprimary)
{
	if (secondorprimary)
	if (SecondaryWeaponLimit <= _Weapon.size())
		secondorprimary = 0;
	if (secondorprimary)
	if (SecondaryWeaponUsePoint<1)
		secondorprimary = 0;

	if ((SecondaryWeapon && secondorprimary && SecondaryWeaponLimit > _Weapon.size() &&
		((SecondaryWeapon == 1 && SecondaryWeaponUsePoint >0) || (SecondaryWeapon == 2 && SecondaryWeaponUsePoint > 0)
		|| (SecondaryWeapon == 3 && SecondaryWeaponUsePoint >0) || SecondaryWeapon == 4 && SecondaryWeaponUsePoint > 0 
		|| SecondaryWeapon == 5 && SecondaryWeaponUsePoint >= 5))

		|| !secondorprimary)
	{
		
		if (!_KnockBack && !isFight && _Action != 0 && _OnLadder != 1 && _OnLadder != 2 && stepOnLadder != 1)
		{
			FightAnimationCount = 0;
			if (!_OnLadder)
			{
				if (!isSatOnGround)
				{
					FightAnimation = 5;
				}
				else
				{
					FightAnimation = 15;
				}
			}
			else
			{
				if (!stepOnLadder)
					switch (stepOnLadderDirection)
				{
					case 0:
					case 2:
						FightAnimation = 21;
						break;
					case 1:
					case 3:
						FightAnimation = 18;
						break;
				}
			}
			isFight = true;
			currentWeaponSorP = secondorprimary;
			secondaryweaponfight = 0;
		}
	}
}

void CSimon::reset()
{
	ObjectCollided.clear();
	LadderCollided.clear();
	_Box.at(0).collisionTime = 1;
	_LadderDirection = -1; 
	flyingObjectVx = 0;
}

void CSimon::OnLanded(int delta)
{
	for (int i = 0; i < ObjectCollided.size(); i++)
	{
		if ((ObjectCollided.at(i).getY() < _Box.at(0).y + 0.9 * _Box.at(0).h
			&& ObjectCollided.at(i).getY() > _Box.at(0).y + 0.1 * _Box.at(0).h)
			|| (ObjectCollided.at(i).getY() < _Box.at(0).y + 0.1 *_Box.at(0).h
			&& ObjectCollided.at(i).getY() + ObjectCollided.at(i).getHeight() > _Box.at(0).y + 0.1 * _Box.at(0).h))
		{
			if (ObjectCollided.at(i).getX() < _Box.at(0).x + 0.5*_Box.at(0).w)
			{
				sideblocked = 1;
				if(Key_Down(DIK_A))
 					_SaveVx = -delta * 0.15;
				break;
			}
			if (ObjectCollided.at(i).getX() > _Box.at(0).x + 0.5*_Box.at(0).w)
			{
				sideblocked = 2;
				if(Key_Down(DIK_D))
					_SaveVx = delta * 0.15;
				break;
			}
		}
		else
		{
			_SaveVx = 0;
			sideblocked = 0;
		}
	}

	if (_Status == 2 && sideblocked == 2)
	{
		_Status = 0;
	}

	if (_Status == 1 && sideblocked == 1)
	{
		_Status = 0;
	}

	switch (_Status)
	{
	case 0:
		//dung yen
		stand(delta);
		break;
	case 1:
		moveLeft(delta);
		break;
	case 2:
		moveRight(delta);
		break;
	}
}

void CSimon::OnFalling(int delta)
{
	setCurrentFrame(0);
	_Box.at(0).vy -= 1.5;
	_Box.at(0).vx = 0;
}

void CSimon::OnJump(int delta)
{
	switch (_JumpAction)
	{
	case 0:
		if (JumpStage(delta))
			_Action = 1;
		break;
	}
}

bool CSimon::_Fight(int delta)
{
	FightAnimationCount += delta;
	if (FightAnimationCount > 100)
	{
		FightAnimation++;
		FightAnimationCount = 0;
	}

	if (!_OnLadder)
	{
		if (!isSatOnGround)
			animate(20, 5, 7, 0);
		else
			animate(20, 15, 17, 0);
	}
	else
	{
		switch (stepOnLadderDirection)
		{
		case 0:
		case 2:
			animate(20, 21, 23, 0);
			break;
		case 1:
		case 3:
			animate(20, 18, 20, 0);
			break;
		}
	}

	int r = rand() % 255;
	MorningStar.Color.setARGB(255, 255 , r , r /2);
	switch (FightAnimation)
	{
	case 5:
	case 15:
		setCurrentFrame(FightAnimation);
		switch (PrimaryWeapon)
		{
		case 0:
			MorningStar.setCurrentFrame(0);
			break;
		case 1:
			MorningStar.setCurrentFrame(4);
			break;
		case 2:
			MorningStar.setCurrentFrame(8);
			break;
		}
		break;
	case 6:
	case 16:
	case 19:
	case 22:
		setCurrentFrame(FightAnimation);
		switch (PrimaryWeapon)
		{
		case 0:
			MorningStar.setCurrentFrame(1);
			break;
		case 1:
			MorningStar.setCurrentFrame(5);
			break;
		case 2:
			MorningStar.setCurrentFrame(9);
			break;
		}
		break;
	case 7:
	case 17:
	case 20:
	case 23:
		setCurrentFrame(FightAnimation);
		switch (PrimaryWeapon)
		{
		case 0:
			MorningStar.setCurrentFrame(2);
			break;
		case 1:
			MorningStar.setCurrentFrame(6);
			break;
		case 2:
			MorningStar.setCurrentFrame(10);
			break;
		}
		break;
	case 8:
	case 24:
		animate(true);
		return 1;
		break;
	case 21:
		if (!_OnLadder || stepOnLadderDirection == 1 || stepOnLadderDirection == 3)
		{
			animate(true);
			return 1;
		}
		else
		{
			if (stepOnLadderDirection == 0 || stepOnLadderDirection == 2)
			{
				setCurrentFrame(FightAnimation);
				MorningStar.setCurrentFrame(0);
			}
		}
		break;
	case 18:
		if (!_OnLadder)
		{
			animate(true);
			return 1;
		}
		else
		{
			if (stepOnLadderDirection == 1 || stepOnLadderDirection == 3)
			{
				setCurrentFrame(FightAnimation);
				MorningStar.setCurrentFrame(0);
			}
		}
		break;
	}

	if (FightAnimation == 7 || FightAnimation == 17 || FightAnimation == 20 || FightAnimation==23)
	{
		if (currentWeaponSorP)
		{
			if (!secondaryweaponfight)
			{
				secondaryweaponfight = 1;
				switch (SecondaryWeapon)
				{
				case 0:
					break;
				case 1:
					dagger.setPosition(getX(), getY());
					dagger.setStatus(1);
					dagger.setFlip(!isFlip());
					_Weapon.push_back(dagger);
					dagger.setStatus(0);
					SecondaryWeaponUsePoint--;
					break;
				case 2:
					holywater.setPosition(getX(), getY());
					holywater.setStatus(1);
					holywater._Box.at(0).vy = 8;
					holywater.setFlip(!isFlip());
					_Weapon.push_back(holywater);
					holywater.setStatus(0);
					SecondaryWeaponUsePoint--;
					break;
				case 3:
					axe.setPosition(getX(), getY());
					axe.setStatus(1);
					axe._Box.at(0).vy = 12;
					axe.setFlip(!isFlip());
					_Weapon.push_back(axe);
					axe.setStatus(0);
					SecondaryWeaponUsePoint--;
					break;
				case 4:
					boomerang.setPosition(getX(), getY());
					boomerang.setStatus(1);
					boomerang.setFlip(!isFlip());
					_Weapon.push_back(boomerang);
					boomerang.setStatus(0);
					SecondaryWeaponUsePoint--;
					break;
				case 5:
					_StopTime = true;
					SecondaryWeaponUsePoint -= 5;
				}
			}
		}
		else
		{
			if (!_OnLadder)
			{
				if (!isSatOnGround)
					animate(50, 5, 7, 0);
				else
					animate(50, 15, 17, 0);
			}
			else
			{
				switch (stepOnLadderDirection)
				{
				case 0:
				case 2:
					animate(50, 21, 23, 0);
					break;
				case 1:
				case 3:
					animate(50, 18, 20, 0);
					break;
				}
			}
			PlaySound(_usingwhipsound);
			if (FightAnimation == 17) //ngoi danh
			{
				switch (PrimaryWeapon)
				{
				case 0:
					if (!isFlip())
						_PrimaryWeapon.InitBox(getBox().x - 56, getBox().y + 8, 56, 10, getBox().vx, getBox().vy);
					else
						_PrimaryWeapon.InitBox(getBox().x + getBox().w, getBox().y + 8, 56, 10, getBox().vx, getBox().vy);
					break;
				case 1:
					if (!isFlip())
						_PrimaryWeapon.InitBox(getBox().x - 56, getBox().y + 8, 56, 10, getBox().vx, getBox().vy);
					else
						_PrimaryWeapon.InitBox(getBox().x + getBox().w, getBox().y + 8, 56, 10, getBox().vx, getBox().vy);
					break;
				case 2:
					if (!isFlip())
						_PrimaryWeapon.InitBox(getBox().x - 90, getBox().y + 8, 90, 10, getBox().vx, getBox().vy);
					else
						_PrimaryWeapon.InitBox(getBox().x + getBox().w, getBox().y + 8, 90, 10, getBox().vx, getBox().vy);
					break;
				}
			}
			else
			{
				switch (PrimaryWeapon)
				{
				case 0:
					if (!isFlip())
						_PrimaryWeapon.InitBox(getBox().x - 56, getBox().y + 34, 56, 10, getBox().vx, getBox().vy);
					else
						_PrimaryWeapon.InitBox(getBox().x + getBox().w, getBox().y + 34, 56, 10, getBox().vx, getBox().vy);
					break;
				case 1:
					if (!isFlip())
						_PrimaryWeapon.InitBox(getBox().x - 56, getBox().y + 34, 56, 10, getBox().vx, getBox().vy);
					else
						_PrimaryWeapon.InitBox(getBox().x + getBox().w, getBox().y + 34, 56, 10, getBox().vx, getBox().vy);
					break;
				case 2:
					if (!isFlip())
						_PrimaryWeapon.InitBox(getBox().x - 90, getBox().y + 34, 90, 10, getBox().vx, getBox().vy);
					else
						_PrimaryWeapon.InitBox(getBox().x + getBox().w, getBox().y + 34, 90, 10, getBox().vx, getBox().vy);
					break;
				}

			}
		}
	}
	return 0;
}

bool CSimon::checkFightCollision()
{
	if (!isKnockBack())
	if (!currentWeaponSorP)
		if (FightAnimation == 7 || FightAnimation == 17 || FightAnimation == 20 || FightAnimation == 23)
			return true;
	return false;
}

bool CSimon::isKnockBack()
{
	return _KnockBack;
}

void CSimon::setKnockBack(bool knockback)
{
	_KnockBack = knockback;
}

void CSimon::input(int delta)
{
	if (!death)
	{
		bool lockturn = false;
		bool isPassingLadder = true; // kiem tra loi di luon khi buoc len thang 
		switch (_OnLadder)
		{
		case 0:
#pragma region
			CollidiefootLadder = false;

			if (_Action != 3)
			{
				if (ObjectCollided.size() == 0)
				{
					if (_Action != 2 && !_KnockBack)
					{
						//neu khong cham gi het, khong nhay, khong bi knock back thi roi xuong
						_Action = 0;
						if (_OnFlyingObject == 1)
							_OnFlyingObject = 2;
					}
				}
				else
				{
					if (!_Action)
					{
						for (int i = 0; i < ObjectCollided.size(); i++)
						{
							if (ObjectCollided.at(i).getDimension() == 3 || ObjectCollided.at(i).getDimension() == 5)
							{
								//neu cham phai vat chan ngan thi ngan khong di di chuyen
								if (_Action == 0)
									lockturn = true;
								//trang thai dung
								_Action = 1;

								if (_OnFlyingObject == 2)
									_OnFlyingObject = 0;
							}
						}
					}
				}
			}
			if (!_KnockBack)
			if (_Action == 1 && !lockturn)
			if (!isFight)
			{
				if (Key_Down(DIK_W) && _Action != 3)
				{
					if (!_LadderDirection)
					{
#pragma region
						int isCollideWithLadder = 0;
						for (int i = 0; i < LadderCollided.size(); i++)
						{
							if (LadderCollided.at(i).getType() == 15)
							{
								bool LadderCollidedIsEmpty = false;
								for (int j = 0; j < LadderCollided.size(); j++)
								{
									if (LadderCollided.at(j).getType() == 13)
									{
										LadderCollidedIsEmpty = true;
										break;
									}
								}
								if (!LadderCollidedIsEmpty)
								{
									ladderposition = 1;
									_OnLadder = 1;
									break;
								}
								isCollideWithLadder = 1;
							}
						}
						if (isCollideWithLadder == 1)
						{
							for (int i = 0; i < LadderCollided.size(); i++)
							{
								if (LadderCollided.at(i).getType() == 13 &&
									LadderCollided.at(i).getY() > _Box.at(0).y - 5 &&
									LadderCollided.at(i).getY() < _Box.at(0).y + 5)
								{
									_OnLadder = 1;
									if (_Box.at(0).x > LadderCollided.at(i).getX() + LadderCollided.at(i).getWidth())
										ladderposition = 1;
									else
										ladderposition = 0;
									break;
								}
							}
						}
#pragma endregion cham thang xuoi
					}
					else
					{
#pragma region
						int isCollideWithLadder = 0;
						for (int i = 0; i < LadderCollided.size(); i++)
						{
							if (LadderCollided.at(i).getType() == 15)
							{
								bool LadderCollidedIsEmpty = false;
								for (int j = 0; j < LadderCollided.size(); j++)
								{
									if (LadderCollided.at(j).getType() == 13)
									{
										LadderCollidedIsEmpty = true;
										break;
									}
								}
								if (!LadderCollidedIsEmpty)
								{
									ladderposition = 1;
									_OnLadder = 1;
									break;
								}
								isCollideWithLadder = 1;
							}
						}
						if (isCollideWithLadder == 1)
						{
							for (int i = 0; i < LadderCollided.size(); i++)
							{
								if (LadderCollided.at(i).getType() == 13 &&
									LadderCollided.at(i).getY() > _Box.at(0).y - 7 &&
									LadderCollided.at(i).getY() < _Box.at(0).y + 7)
								{
									_OnLadder = 1;
									if (_Box.at(0).x > LadderCollided.at(i).getX() + LadderCollided.at(i).getWidth())
										ladderposition = 1;
									else
										ladderposition = 0;
									break;
								}
							}
						}

#pragma endregion cham thang nguoc
					}
				}
				if (Key_Down(DIK_S) && _Action != 3)
				{
					int isCollideWithLadder;
					bool canSit = true;
					for (int i = 0; i < LadderCollided.size(); i++)
					{
						if (LadderCollided.at(i).getType() == 16)
						{
							canSit = false;
						}
					}

					if (canSit)
					{
#pragma region
						if (!isSatOnGround)
						{
							isSatOnGround = true;
							_Box.at(0).vy += 18;
							_Box.at(0).h -= 18;
							SwiftToSit = true;
							isStand = false;
							SwiftToStand = false;
						}
#pragma endregion ngoi xuong
					}
					else
						switch (_LadderDirection)
					{
						case 0:
#pragma region
							isCollideWithLadder = 0;
							for (int i = 0; i < LadderCollided.size(); i++)
							{
								if (LadderCollided.at(i).getType() == 16)
								{
									bool  LadderCollidedIsEmpty = false;
									for (int j = 0; j < LadderCollided.size(); j++)
									{
										if (LadderCollided.at(j).getType() == 13 || LadderCollided.at(j).getType() == 14)
										{
											LadderCollidedIsEmpty = true;
											break;
										}
									}
									if (!LadderCollidedIsEmpty)
									{
										ladderposition = 0;
										_OnLadder = 2;
									}
									isCollideWithLadder = 1;
								}
							}
							if (isCollideWithLadder == 1)
							{
								for (int i = 0; i < LadderCollided.size(); i++)
								{
									if ((LadderCollided.at(i).getType() == 13 || LadderCollided.at(i).getType() == 14) &&
										LadderCollided.at(i).getY() + LadderCollided.at(i).getHeight()> _Box.at(0).y - 7 &&
										LadderCollided.at(i).getY() + LadderCollided.at(i).getHeight()< _Box.at(0).y + 7)
									{
										_OnLadder = 2;
										if (_Box.at(0).x > LadderCollided.at(i).getX() + LadderCollided.at(i).getWidth())
											ladderposition = 0;
										else
											ladderposition = 1;
										break;
									}
								}
							}
#pragma endregion cham thang xuoi
							break;
						case 1:
#pragma region
							isCollideWithLadder = 0;
							for (int i = 0; i < LadderCollided.size(); i++)
							{
								if (LadderCollided.at(i).getType() == 16)
								{
									bool  LadderCollidedIsEmpty = false;
									for (int j = 0; j < LadderCollided.size(); j++)
									{
										if (LadderCollided.at(j).getType() == 13 || LadderCollided.at(j).getType() == 14)
										{
											LadderCollidedIsEmpty = true;
											break;
										}
									}
									if (!LadderCollidedIsEmpty)
									{
										ladderposition = 1;
										_OnLadder = 2;
									}
									isCollideWithLadder = 1;
								}
							}
							if (isCollideWithLadder == 1)
							{
								for (int i = 0; i < LadderCollided.size(); i++)
								{
									if ((LadderCollided.at(i).getType() == 13 || LadderCollided.at(i).getType() == 14) &&
										LadderCollided.at(i).getY() + LadderCollided.at(i).getHeight()> _Box.at(0).y - 7 &&
										LadderCollided.at(i).getY() + LadderCollided.at(i).getHeight()< _Box.at(0).y + 7)
									{
										_OnLadder = 2;
										if (_Box.at(0).x > LadderCollided.at(i).getX())
											ladderposition = 1;
										else
											ladderposition = 0;
										break;
									}
								}
							}
#pragma endregion cham thang nguoc
							break;
					}
				}
				else
				{
#pragma region
					if (isSatOnGround)
					{
						if (!isFight)
						{
							isSatOnGround = false;
							animate(30, 0, 0);
							_Box.at(0).vy -= 18;
							_Box.at(0).h += 18;
							SwiftToStand = true;
							isStand = true;
						}
					}
#pragma endregion dung len khi ngoi xuong
				}

				if (!isSatOnGround)
				{
					if (Key_Down(DIK_D))
						_Status = 2;
					if (Key_Down(DIK_A))
						_Status = 1;
				}
			}

			if (SwiftToSit)
			{
				_Box.at(0).vy -= 18;
				SwiftToSit = false;
			}

			if (SwiftToStand)
			{
				_Box.at(0).vy += 18;
				SwiftToStand = false;
			}

			switch (_Action)
			{
			case 0:
				OnFalling(delta);
				break;
			case 1:
				OnLanded(delta);
				break;
			case 2:
				OnJump(delta);
				break;
			case 3:
#pragma region
				CSprite::animate(30, 0, 3);
				if (!goInCastle)
				if (getX() > CastleGateX)
				{
					moveLeft(delta / 4);
				}
				else
					goInCastle = true;

				if (goInCastle)
				{
					if (getX() + getWidth() / 2 >= CastleGateX + CastleGateWidth)
					{
						if (!isFlip())
						{
							moveRight(delta / 4);
							_Flip.at(0) = true;
						}
						startGoinCastle = true;
						_Box.at(0).vx = 0;
					}
				}
				if (!isCollideWithCastleGate)
					_Action = 1;
				isCollideWithCastleGate = false;
#pragma endregion vao cua lau dai
				break;
			}
#pragma endregion khong tren thang
			break;
		case 1:
#pragma region
			
			for (int i = 0; i < LadderCollided.size(); i++)
			{
				if (LadderCollided.at(i).getType() == 13 &&
					LadderCollided.at(i).getY() > _Box.at(0).y - 5 &&
					LadderCollided.at(i).getY() < _Box.at(0).y + 5)
				{
					footLadder = LadderCollided.at(i);
					CollidiefootLadder = true;
				}
				if (LadderCollided.at(i).getType() == 15 || LadderCollided.at(i).getType() == 16)
				{
					isPassingLadder = false;
				}
			}

			if (!_LadderDirection)
			{
				if (ladderposition)
				{
					moveRight(delta);
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x > footLadder.getX() - 10)
					{
						_Box.at(0).x = footLadder.getX() - 10;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 0;
					}
				}
				else
				{
					moveLeft(delta);
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x < footLadder.getX() - 10)
					{
						_Box.at(0).x = footLadder.getX() - 10;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 0;
					}
				}
			}
			else
			{
				if (ladderposition)
				{
					moveLeft(delta);
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x < footLadder.getX() + 16)
					{
						_Box.at(0).x = footLadder.getX() + 16;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 2;
					}
				}
				else
				{
					moveRight(delta);
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x > footLadder.getX() + 16)
					{
						_Box.at(0).x = footLadder.getX() + 16;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 2;
					}
				}
			}
#pragma endregion buoc len thang 
			break;
		case 2:
#pragma region
			for (int i = 0; i < LadderCollided.size(); i++)
			{
				if ((LadderCollided.at(i).getType() == 13 || LadderCollided.at(i).getType() == 14) &&
					LadderCollided.at(i).getY() + LadderCollided.at(i).getHeight() > _Box.at(0).y - 5 &&
					LadderCollided.at(i).getY() + LadderCollided.at(i).getHeight() < _Box.at(0).y + 5)
				{
					footLadder = LadderCollided.at(i);
					CollidiefootLadder = true;
				}
				if (LadderCollided.at(i).getType() == 15 || LadderCollided.at(i).getType() == 16)
				{
					isPassingLadder = false;
				}
			}
			if (!_LadderDirection)
			{
				if (ladderposition)
				{
					moveRight(delta);
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x > footLadder.getX() + 18)
					{
						_Box.at(0).x = footLadder.getX() + 18;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 1;
					}
				}
				else
				{
					moveLeft(delta);
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x < footLadder.getX() + 23)
					{
						_Box.at(0).x = footLadder.getX() + 23;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 1;
					}
				}
			}
			else
			{
				if (ladderposition)
				{
					moveRight(delta);
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x > footLadder.getX() - 16)
					{
						_Box.at(0).x = footLadder.getX() - 16;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 3;
					}
				}
				else
				{
					moveLeft(delta); 
					if (isPassingLadder)
					{
						_OnLadder = 0;
					}
					if (CollidiefootLadder)
					if (_Box.at(0).x < footLadder.getX() - 16)
					{
						_Box.at(0).x = footLadder.getX() - 16;
						_OnLadder = 3;
						stepOnLadder = 1;
						stepOnLadderDirection = 3;
					}
				}
			}
#pragma endregion buoc xuong thang 
			break;
		case 3:
#pragma region
			switch (stepOnLadder)
			{
			case 0:
#pragma region
				switch (stepOnLadderDirection)
				{
				case 0:
					animate(37, 12, 12);
					break;
				case 1:
					animate(37, 10, 10);
					break;
				case 2:
					animate(37, 12, 12);
					break;
				case 3:
					animate(37, 10, 10);
					break;
				}
				stepOnLadderHeight = 0;
				_Box.at(0).vx = 0;
				_Box.at(0).vy = 0;

				switch (QueueFight)
				{
				case 1:
					fight(0);
					QueueFight = 0;
					break;
				case 2:
					QueueFight = 0;
					fight(1);
					break;
				}
				if (!isFight)
				{

					if (Key_Down(DIK_W))
					{
						if (Key_Down(DIK_RETURN))
						{
							fight(1);
						}
						else
						{
							if (stepOnLadderDirection == 1)
							{
								stepOnLadderDirection = 0;
							}
							if (stepOnLadderDirection == 3)
							{
								stepOnLadderDirection = 2;
							}
							stepOnLadder = 1;
						}
					}

					if (Key_Down(DIK_S))
					{
						if (stepOnLadderDirection == 0)
						{
							stepOnLadderDirection = 1;
						}
						if (stepOnLadderDirection == 2)
						{
							stepOnLadderDirection = 3;
						}
						stepOnLadder = 1;
					}

					if (Key_Down(DIK_A))
					{
						if (stepOnLadderDirection == 0)
						{
							stepOnLadderDirection = 1;
						}
						if (stepOnLadderDirection == 3)
						{
							stepOnLadderDirection = 2;
						}
						stepOnLadder = 1;
					}
					if (Key_Down(DIK_D))
					{
						if (stepOnLadderDirection == 1)
						{
							stepOnLadderDirection = 0;
						}
						if (stepOnLadderDirection == 2)
						{
							stepOnLadderDirection = 3;
						}
						stepOnLadder = 1;
					}

					for (int i = 0; i < LadderCollided.size(); i++)
					{
						if ((LadderCollided.at(i).getType() == 16 || LadderCollided.at(i).getType() == 15) &&
							LadderCollided.at(i).getY() > _Box.at(0).y - 7 &&
							LadderCollided.at(i).getY() < _Box.at(0).y + 7)
						{
							_OnLadder = 0;
							stepOnLadder = 0;
							break;
						}
					}
					
				}
#pragma endregion dung yen tren thang
				break;
			case 1:
				if (Key_Down(DIK_RETURN))
				{
					if (Key_Down(DIK_W))
					{
						if (SecondaryWeaponUsePoint>0)
						QueueFight = 2;
						else
							QueueFight = 1;
					}
					else
						QueueFight = 1;
				}
#pragma region
				if (!isFight)
					switch (stepOnLadderDirection)
				{
					case 0:
#pragma region
						animate(37, 12, 13);
						_Box.at(0).vx = 1;
						_Box.at(0).vy = 1;
						stepOnLadderHeight += 1;
						if (stepOnLadderHeight >= 16)
						{
							stepOnLadder = 0;
							stepOnLadderHeight = 0;
						}
#pragma endregion len thang theo huong cheo tu trai sang phai(vx > 0, vy >0)
						break;
					case 1:
#pragma region
						animate(37, 10, 11);
						_Box.at(0).vx = -1;
						_Box.at(0).vy = -1;
						stepOnLadderHeight += 1;
						if (stepOnLadderHeight >= 16)
						{
							stepOnLadder = 0;
							stepOnLadderHeight = 0;
						}
#pragma endregion xuong thang theo huong cheo tu phai sang trai(vx < 0, vy < 0)
						break;
					case 2:
#pragma region
						animate(37, 12, 13);
						_Box.at(0).vx = -1;
						_Box.at(0).vy = 1;
						stepOnLadderHeight += 1;
						if (stepOnLadderHeight >= 16)
						{
							stepOnLadder = 0;
							stepOnLadderHeight = 0;
						}
#pragma endregion len thang theo huong tu phai sang trai (vx < 0, vy > 0)
						break;
					case 3:
#pragma region
						animate(37, 10, 11);
						_Box.at(0).vx = 1;
						_Box.at(0).vy = -1;
						stepOnLadderHeight += 1;
						if (stepOnLadderHeight >= 16)
						{
							stepOnLadder = 0;
							stepOnLadderHeight = 0;
						}
#pragma endregion xuong thang theo huong tu trai sang phai
						break;
				}
#pragma endregion di chuyen tren thang
				break;
			}
			break;
#pragma endregion buoc tren thang va roi khoi thang
		}
#pragma region
		{
			if (isFight)
			{
				animate(false);
				if (_Fight(delta))
					isFight = false;
			}
		}
#pragma endregion su dung roi
	}
}

void CSimon::update(int delta)
{
	if (_StopTime)
	{
		_StoptimeWaitingCount += delta;
		if (_StoptimeWaitingCount > _StoptimeWaitingLimit)
		{
			_StoptimeWaitingCount = 0;
			_StopTime = false;
		}
	}

	if (_Box.at(0).vx < 0)
		_Flip.at(0) = false;
	else
	if (_Box.at(0).vx > 0)
		_Flip.at(0) = true;

	if (_Action != 2&&!_KnockBack)
		if (_Box.at(0).collisionTime != 1)
		{
			if (sideblocked != 0 && _Action != 1)
				_Box.at(0).vx = _Box.at(0).vx * _Box.at(0).collisionTime;
			_Box.at(0).vy = _Box.at(0).vy * _Box.at(0).collisionTime;
			
		}

	if (cmr.pos.x >= _Box.at(0).x)
		if (_Box.at(0).vx < 0)
			_Box.at(0).vx = 0;
	if (cmr.pos.x + SCREENWIDTH < _Box.at(0).x + _Box.at(0).w)
	if (_Box.at(0).vx > 0)
			_Box.at(0).vx = 0;

	_Box.at(0).x += _Box.at(0).vx + flyingObjectVx;
	_Box.at(0).y += _Box.at(0).vy;

	for (int i = 0; i < _Weapon.size(); i++)
	{
		_Weapon.at(i).update(delta);
		if (_Weapon.at(i).getStatus() == 100)
		{
			_Weapon.erase(_Weapon.begin() + i);
		}
		else
		if (_Weapon.at(i).getType() == 4)
		{
			if ((isFlip() && _Weapon.at(i)._Box.at(0).vx < 0) || (!isFlip() && _Weapon.at(i)._Box.at(0).vx>0))
			{
				Box newbx = _Weapon.at(i).getBox();
				Box newbx2 = getBox();
				newbx2.vx += newbx.vx;
				int dimension = CollideCheck(newbx2, newbx);
				if (dimension == 5 || dimension == 1 || dimension == 2)
				{
					_Weapon.erase(_Weapon.begin() + i);
				}
			}
		}
	}

	if (_OnLadder==3)
	if (LadderCollided.size() == 0)
	{
		_OnLadder = 0;
		stepOnLadder = 0;
	}

	//Weapon
	if (!isKnockBack() && invulnerable && HealthPoint < 0)
	{
		death = true;
	}
}

bool CSimon::isFighting()
{
	return isFight;
}

void CSimon::render(int delta)
{
	if (!death)
	{
#pragma region
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
			MorningStar.Color.setA(invulnerablecount);
			if (invulnerablecounttime == 5)
			{
				invulnerablecounttime = 0;
				invulnerable = false;
				invulnerablecount = 0;
				invulnerablecounttime = 0;
				Color.setA(255);
				MorningStar.Color.setA(255);
			}
		}

		if (!startGoinCastle)
		{
			D3DXVECTOR2 TransformPosition;
			if (getCurrentFrame() != 4 && getCurrentFrame() != 15 && getCurrentFrame() != 16 && getCurrentFrame() != 17)
				TransformPosition = cmr.GetPointTransform(_Box.at(0).x + 14, _Box.at(0).y + _Box.at(0).h / 2);
			else
				TransformPosition = cmr.GetPointTransform(_Box.at(0).x + 14, _Box.at(0).y + _Box.at(0).h / 2 - 9);

			if (_Flip.at(0))
			{
				MorningStar.setFlip(1);
				flip(delta, TransformPosition.x, TransformPosition.y);
			}
			else
			{
				draw(delta, TransformPosition.x, TransformPosition.y);
				MorningStar.setFlip(0);
			}
			if (currentWeaponSorP == 0)	//neu su dung roi
			if (isFight)
			{
				if (isFlip())
				{
					if (!isSatOnGround)
						MorningStar.setPosition(getX() + 28, getY());
					else
						MorningStar.setPosition(getX() + 28, getY() - 5);
				}
				else
				{
					if (!isSatOnGround)
						MorningStar.setPosition(getX() - 28, getY());
					else
						MorningStar.setPosition(getX() - 28, getY() - 5);
				}
				MorningStar.render(delta);
			}
			else
				MorningStar.setCurrentFrame(3);
		}
		else
		{
			D3DXVECTOR2 TransformPosition;
			TransformPosition = cmr.GetPointTransform(_Box.at(0).x + 14, _Box.at(0).y + _Box.at(0).h / 2);
			_TempWidth -= delta * 0.05;
			if (_TempWidth < 0)
			{
				nextlevel = true;
				startGoinCastle = false;
				_Action = 1;
				_TempWidth = 0;
			}

			if (_Flip.at(0))
			{
				specificfliprenderforsimon(TransformPosition.x, TransformPosition.y, _TempWidth);
			}
			else
			{
				specificrenderforsimon(TransformPosition.x, TransformPosition.y, _TempWidth);
			}
		}
#pragma endregion luc con song
	}
	else
#pragma region
		{
			if (!isSatOnGround)
				DeathSprite.setPosition(getX(), getY());
			else
				DeathSprite.setPosition(getX(), getY() + 8);
			DeathSprite.setFlip(isFlip());
			DeathSprite.render(delta);
			waitingtime += delta;
			_Box.at(0).vx = 0;
			_Box.at(0).vy = 0;
			if (waitingtime > 1500)
			{
				waitingtime = 0;
				isReset = true;
				death = false;
			}
		}	
#pragma endregion luc chet

		//render weapon
		for (int i = 0; i < _Weapon.size(); i++)
		{
			_Weapon.at(i).render(delta);
		}

}

Box CSimon::getPrimaryBox()
{
	return _PrimaryWeapon;
}
#ifndef _SIMON_H
#define _SIMON_H

#include "sprite.h"
#include "SweptAABB.h"
#include "weapon.h"
class BoxCollision
{
private:
	int _Type;
	int _Dimension;
	int _Id;
	float _X, _Y;
	float _H, _W;
public:
	BoxCollision();
	BoxCollision(int, int, int, float, float);
	BoxCollision(int, int, int, float, float, float, float);
	BoxCollision(int ,int ,int);
	void setType(int);
	void setDimension(int);
	void setId(int);
	void setXY(float, float);
	void setWidth(float);
	void setHeight(float);
	int getId();
	int getType();
	int getDimension();
	float getX();
	float getY();
	float getWidth();
	float getHeight();
};

class CSimon : public CSprite
{
private:
	
	CSound *_usingwhipsound;
	int _Status;
	Box _PrimaryWeapon;
	float vy = 0;
	float _Vy, _Vx;
	bool _FightInitialize;
	float _Gravity;
	float _AccelerateY;
	float _AccelerateX;
	bool _Jump;
	bool _resetJump;
	vector<int> ListRightCollision;
	vector<int> ListLeftCollision;

	//saving vx when jump and collide a block
	float	_SaveVx;
	bool _OnJumpUpCollision;
	void OnLanded(int);
	void OnJump(int);
	void OnFalling(int);
	int _JumpAction;

	bool CheckHorizontalCollision(Box, BoxCollision);
	bool CheckVerticalCollision(Box, BoxCollision);
	bool startGoinCastle;
	float _TempWidth;

	CSprite	MorningStar;
	bool	ladderposition; // thang cham vao simon thi 0, khong cham simon thi 1
	BoxCollision footLadder;
	bool	CollidiefootLadder;
	int		stepOnLadder;
	bool	isSatOnGround;
	int		stepOnLadderDirection;
	float	stepOnLadderHeight;

	bool	isFight;
	int		FightAnimation;
	int		FightAnimationCount;
	bool	_Fight(int delta);
	bool	_KnockBack;

	int		invulnerableCountInvert;
	int		invulnerablecounttime;
	int		invulnerablecount;
	float	checkpointX, checkpointY;
	int		secondaryweaponfight;
	cweapon dagger, holywater, axe, boomerang, stopwatch;
	int		QueueFight;
	float	flyingObjectVx;
	

	int _StoptimeWaitingLimit;
	int _StoptimeWaitingCount;
	bool _StopTime;
	
public:
	int _OnFlyingObject;
	bool isCollideWithCastleGate;
	bool isFighting();
	bool	isStopTime();
	void	setflyingObjectVx(float vx);
	float	getflyingObjectVx();
	

	//vu khi thu 2 cua simon
	vector<cweapon> _Weapon;

	//current using secondary or primary weapon
	int		currentWeaponSorP;
	
	int		isReset;
	void	CreateCheckPoint();
	void	ResetToCheckPoint();
	int		waitingtime;

	int		death;
	CSprite	DeathSprite;
	//thong tin ve mau
	int		HealthPoint;

	//thong tin ve roi
	int		PrimaryWeapon;

	//thong tin ve vu khi thu 2
	int		SecondaryWeapon;
	int		SecondaryWeaponUsePoint;
	int		SecondaryWeaponLimit;

	//so diem
	int	score;

	//reset lai nhan vat
	void	resetCharacter();
	void	resetCharacterForNextLevel();

	bool	invulnerable;
	bool	isKnockBack();
	void	setKnockBack(bool trueorfalse);
	void	endJump();
	bool	_JumpInitialize;

	int		GetStepOnLadderDirection();
	bool	nextlevel;
	bool	goInCastle;
	float	CastleGateX;
	float	CastleGateWidth;
	bool	SwiftToSit;
	int		_Action;
	bool	SwiftToStand;
	bool	isStand;
	int		sideblocked;
	int		_OnLadder;
	float	_LadderX, _LadderY;
	int		_FlagUp, _FlagDown;
	int		_LadderDirection;
	vector<BoxCollision> LadderCollided;
	vector<BoxCollision> ObjectCollided;
	void load(char* filepath,int columns, int rows);
	CSimon();
	~CSimon();
	int		getStatus();
	void	setStatus(int);
	void	update(int);
	void	usingXCross(int);
	void	usingHolyWater(int);
	void	usingAxe(int);
	void	render(int);
	void	input(int);
	Box		getPrimaryBox();
	int		isJump();
	void	reset();

	void	stand(int);
	void	moveLeft(int);
	void	moveRight(int);
	int		JumpStage(int);
	void	useWeapon();
	int		knockBack();
	bool	checkFightCollision();
	void	fight(int secondorprimary);
	void	jump();
};

#endif
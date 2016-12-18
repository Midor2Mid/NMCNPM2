#ifndef _GAMEPLAY_H
#define _GAMEPLAY_H

#include "sprite.h"
#include "zombie.h"
#include "skeleton.h"
#include "medusahead.h"
#include "lancer.h"
#include "fishmonster.h"
#include "armorevil.h"
#include "Bat.h"
#include "catdemon.h"
#include "bossbat.h"
#include "bossmedusa.h"
#include "dragoncannon.h"
#include "ghost.h"
#include "candle.h"
#include "largecandle.h"
#include "door.h"
#include "loadfile.h"
#include "simon.h"
#include "font.h"
#include "splashwater.h"
#include "item.h"
#include "healthbar.h"
#include "spiketrap.h"
#include "dxaudio.h"
#include "flyingblock.h"
#include "snake.h"
class CGamePlay
{
private:

	//sound
	CSound			*levelmusic;
	CSound			*hitmonster;
	CSound			*hitcannon;
	CSound			*collectitem;
	CSound			*holywater;
	CSound			*holycross;
	CSound			*weaponcollect;
	CSound			*bossmusic;
	CSound			*clearstage;
	CSound			*deathsound;
	CSound			*opendoorsound;
	CSound			*fallingsound;
	CSound			*decreaseweaponusepointsound;
	CSound			*fallingdownwatersurface;

	CSprite		    blackboardpause;
	CSprite			pausemenusprite;
	char			*pausemenuitem[3];
	int				pausemenu;
	CFont			arialsmaller;
	CFont			arialbigger;
	int				currentchoosenpausedmenu;

	int				iseatencrystal;
	int				winningScene;
	int				timeregainperhealth;//thoi gian moi mot cot mau hoi
	int				currenttimeregainperhealth;
	int				timewaitingfornextlevel;

	int				holycrosscount;
	int				isactiveholycross;

	int				_playdeathsound;
	int				leveltime;
	CSprite			SecondaryWeapon[5];
	CSprite			SecondaryWeaponLimit[2];
	LoadFile		loadObject;

	CSprite			MainBackGround;
	vector<int>		listObjectDead;
	vector<int>		ListEnemies;
	vector<int>		listActiveEnemies;
	vector<int>		listSpecialObject;
	vector<int>		listActiveSpecialObject;
	map<int, int>	_DirectGetType;
	//Object
	CBat			bat;
	CArmorevil		armorevil;
	CCat			cat;
	CFish			fish;
	CLancer			lancer;
	CMedusahead		medusahead;
	CSkeleton		skeleton;
	CZombie			zombie;
	CBossbat		bossbat;
	CBossmedusa		bossmedusa;
	vector<csnake>	medusasub;
	csnake			snake;
	CGhost			ghost;
	CDragonCannon	dragoncannon;
	CCandle			candle;
	CLargeCandle	largecandle;
	CDoor			door;
	cspiketrap		spiketrap;
	cflyingblock	flyingblock;
	CSprite			StaticObject[11];
	CSprite			*Object[28];
	CSprite			gameboard;
	CSprite			DoorAnimation;
	chealthbar		healthbar;
	//item
	citem			itemsprite[14];
	vector<citem>	Item;
	//effect
	vector<CSprite>			hit;
	vector<CSprite>			destroyflame;
	vector<CSplashWater>	SplashWater;
	CSplashWater			_splashwater;

	//link
	vector<string>			additionallink;
	vector<string>			itemlink;
	//camera
	vector<vector<float>>	cameraMaxX;
	vector<vector<float>>	cameraMinX;

	//CSprite			itemboard
	CFont			arial;
	CSimon			simon;
	CSprite			sprite, sprite2;
	int		currentstage = 0;
	int		level;
	int		onGate;
	float	gateX;
	float	gateY;
	int	    touchGateOnAir;
	int		currentGateID;

	int		gamescore = 0;
	int		gameremainingtime;
	void	changecamera(int); 
	int		simonstage;
	bool	bossBattle;

	void _savegame(char* filename);
	vector<string> gamesave;
	bool isloadsavinggame;
public:
	void LoadSaveGame();
	int isExit;
	int isActiveHolyCross();
	CGamePlay();
	void	GeneratingItem(Box DestroyedObject);
	vector<Box> ObjectDead;
	void	LoadMap();
	int		OnKeyUp(int);
	int		OnKeyDown(int);
	void	initialize();
	void	update(int);
	void	render(int);
	void	renderText(int);
	void	resetCamera();
};

#endif // !_GAMEPLAY_H

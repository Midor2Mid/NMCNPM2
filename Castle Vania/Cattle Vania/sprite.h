#ifndef _SPRITE_H
#define _SPRITE_H
#include	<d3dx9.h>
#include	<vector>
#include	"global.h"
#include	"camera.h"
#include	"SweptAABB.h"
#include	"map"
using namespace std;

class CColor
{
public:
	int _r, _g, _b, _a;
	CColor(int a, int r, int g, int b);
	~CColor();
	CColor();
	CColor operator = (const CColor& other);
	void setARGB(int, int, int, int);
	void setR(int);
	void setG(int);
	void setB(int);
	void setA(int);
	int getR();
	int getG();
	int getB();
	int getA();
};


class CGameObject{
private:
	float _x, _y;
public:
	CGameObject();
	~CGameObject();
	void setPosition(int, int);
	void setX(int);
	void setY(int);
	float getX();
	float getY();
};

class CSprite
{
private:
	float	_Width, _Height;
	int		_Columns, _Rows;
	int		_StartFrame, _LastFrame, _CurrentFrame;
	int		_AnimationTick;
	bool	_CspriteLoad;
	int		_AnimationDelay, _AnimationCount;
	bool	_AnimationPlay;
	bool	_IsAnimationEnd;
	float	_DeltaFlip;
	D3DXIMAGE_INFO		_Info;
	D3DLOCKED_RECT		_LockRect;

	int				_NonFlip;
	vector<int>		_Type;		//chia cac tile trong 1 texture thanh cac vung khac nhau
	int				_RepeatAnimation = true;
	map<int, int>	_DirectOrder;

public:
	LPDIRECT3DTEXTURE9	_Texture;
	int manualFind(int);
	CSprite();
	~CSprite();
	void	animate(int);
	CColor Color;
	int alphablend;


	float Vx, Vy;
	vector<Box>				_Box;
	vector<int>				_Flip;
	vector<int>				_Id;
	vector<int>				_Camera;

	int				findVectorPosition(int);
	void			setDeltaFlip(float);
	void			setFlip(int);
	void			setFlip(int, int);
	void			setId(int, int);
	virtual void	addNewObject(float, float, int);
	virtual void	addNewObject(int id, float x, float y, float width, float height, int flip);
	virtual void	addNewObject(int, float, float, int, int); //id x y camera
	virtual void	addNewObject(int, int, float, float, int, int);	// id type x y camera
	float			getWidth();
	float			getHeight();
	float			getX();
	float			getX(int);
	float			getY();
	float			getY(int);
	int				getType(int);
	int				getCurrentFrame();
	int				getCamera();
	int				getRows();
	int				getColumns();
	vector<Box>		getVectorBox();
	vector<Box>		getVectorBox(int, int);
	virtual int		getStatus();
	virtual int		getStatus(int id);
	virtual void	setStatus(int, int);
	virtual int		getHealth();
	void	setCurrentFrame(int);
	void	setWidth(int);
	void	setHeight(int);
	void	setSize(int, int);
	void	setLastFrame(int);
	void	setCamera(int);
	void	setX(float);
	void	setY(float);
	void	setX(float, int);
	void	setY(float, int);
	void	setNonFlip(int);
	bool	isAnimationEnd();
	bool	isAnimate();
	int		isFlip();
	int		isFlip(int);
	bool	isLoad();
	int		readPixel(int, int);
	CColor	readPixelARGB(int, int);
	virtual void moveX(int);
	virtual void moveX(int, int);
	virtual void moveY(int);
	virtual void moveY(int, int);
	virtual void move(float, float);
	virtual void load(char*, int, int);
	virtual void load(char*, int, int, int);
	virtual void load(char*);
	virtual void load(char*, int);
	virtual void loadBackGround(char*);
	virtual void setPosition(float, float);
	virtual void setPosition(float, float, int);
	virtual void update(int, int);
	virtual void update(int, Box, int);
	virtual void update(int);
	virtual void getObject(Box);
	void	tranferX(float);
	void	tranferY(float);
	void	renderTile(int);
	void	renderTile(int, int);
	void	render(int);
	void	renderOne(int);

	void	renderMergeObject(int delta, int id);

	virtual	void	flip(int, float, float);
	virtual	void	draw(int, float, float);
	virtual int		render(int delta, int id);
	virtual int		isActive(int);
	void	animate(int, int, int);
	void	animate(int, int, int, int);
	void	animate(bool);
	void	setAnimateDelay(int);
	Box		getBox();
	Box		getBox(int);
	void	Clear();
	virtual void	ClearAll();
	void	Delete(int);
	int		compareTwoTile(int, int);
	int		saveTexture(vector<int>, char*);
	//specific render for simon
	void    specificrenderforsimon(float, float, float);
	void    specificfliprenderforsimon(float, float, float);
};

#endif // !_SPRITE_H
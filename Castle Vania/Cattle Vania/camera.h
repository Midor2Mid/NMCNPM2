#ifndef _CAMERA_H
#define	_CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "global.h"
class camera
{
private:
	float _MaxMovingX;
	float _MaxMovingY;
	float _MinMovingX;
	float _MinMovingY;
public:
	float getMaxMovingX();
	D3DXVECTOR2 pos;
	D3DXMATRIX MatrixTransform;
	camera(void);
	~camera(void);
	void Update(float);
	void UpdateMapEditor(float, float);
	void UpdateWorldMap(float, float);
	D3DXVECTOR2 GetPointTransform(float x, float y);
	void setMaxMovingX(float);
	void setMaxMovingY(float);
	void setMinMovingX(float);
	void setMinMovingY(float);
};
#endif 
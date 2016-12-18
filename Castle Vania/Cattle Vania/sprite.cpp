#include "sprite.h"
#include "dxgraphics.h"

CSprite::CSprite()
{
	_CspriteLoad = false;
}

CSprite::~CSprite()
{

}

void CSprite::loadBackGround(char* filename)
{
	HRESULT result;
	D3DXIMAGE_INFO _Info;
	D3DXGetImageInfoFromFile(filename, &_Info);
	_Width = _Info.Width;
	_Height = _Info.Height;
	//create the new texture by loading a bitmap image file
	result = D3DXCreateTextureFromFileEx(
		d3ddev,              //Direct3D device object
		filename,            //bitmap filename
		_Width,          //bitmap image width
		_Height,         //bitmap image height
		0,                   //mip-map levels (1 for no chain)
		0,     //the type of surface (standard)
		D3DFMT_A8R8G8B8,      //surface format (default)
		D3DPOOL_MANAGED,     //memory class for the texture
		D3DX_FILTER_NONE,        //image filter
		D3DX_FILTER_BOX,        //mip filter
		D3DCOLOR_XRGB(255, 0, 255),          //color key for transparency
		&_Info,							//bitmap file info (from loaded file)
		NULL,						//color palette
		&this->_Texture);          //destination texture
	//make sure the bitmap texture was loaded correctly
	if (result != D3D_OK)
		MessageBox(NULL, "sai duong dan len file hinh", "error Texture", MB_OK);
	_Columns = _Width / 64;
	_Rows = _Height / 64;
	_Width = _Width / _Columns;
	_Height = _Height / _Rows;
	_StartFrame = 0;
	_CurrentFrame = 0;
	_LastFrame = _Columns - 1;
	_AnimationDelay = 5;
	_AnimationCount = 0;
	alphablend = 255;
	_DeltaFlip = 0;
	Vx = 0;
	Vy = 0;
	_IsAnimationEnd = false;
	_Camera.push_back(0);
	_Id.push_back(0);
	_DirectOrder[0] = 0;
	bool flip = false;
	_Flip.push_back(flip);

	Box bx(-_Width / 2, -_Height / 2, _Width, _Height, 0, 0);
	_Box.push_back(bx);
	_CspriteLoad = true;
	_NonFlip = 0;
}

void CSprite::load(char* filename, int columns, int rows)
{
	_Columns = columns;
	_Rows = rows;
	HRESULT result;
	D3DXIMAGE_INFO _Info;
	D3DXGetImageInfoFromFile(filename, &_Info);
	_Width = _Info.Width;
	_Height = _Info.Height;
	//create the new texture by loading a bitmap image file
	result = D3DXCreateTextureFromFileEx(
		d3ddev,              //Direct3D device object
		filename,            //bitmap filename
		_Width,          //bitmap image width
		_Height,         //bitmap image height
		1,                   //mip-map levels (1 for no chain)
		0,     //the type of surface (standard)
		D3DFMT_A8R8G8B8,      //surface format (default)
		D3DPOOL_MANAGED,     //memory class for the texture
		D3DX_FILTER_NONE,        //image filter
		D3DX_FILTER_BOX,        //mip filter
		D3DCOLOR_XRGB(255, 0, 255),          //color key for transparency
		&_Info,							//bitmap file info (from loaded file)
		NULL,						//color palette
		&this->_Texture);          //destination texture
	//make sure the bitmap texture was loaded correctly
	if (result != D3D_OK)
		MessageBox(NULL, "sai duong dan len file hinh", "error Texture", MB_OK);

	_Width = _Width / _Columns;
	_Height = _Height / _Rows;
	_StartFrame = 0;
	_CurrentFrame = 0;
	_LastFrame = _Columns - 1;
	_AnimationDelay = 5;
	_AnimationCount = 0;
	alphablend = 255;
	_DeltaFlip = 0;
	Vx = 0;
	Vy = 0;
	_IsAnimationEnd = false;
	_Camera.push_back(0);

	_Id.push_back(0);
	_DirectOrder[0] = 0;
	_Flip.push_back(false);
	//_Active.push_back(false);

	Box bx(-_Width / 2, -_Height / 2, _Width, _Height, 0, 0);
	_Box.push_back(bx);
	_CspriteLoad = true;
	_NonFlip = 0;
}

void CSprite::load(char* filename, int columns, int rows, int id)
{
	_Columns = columns;
	_Rows = rows;
	HRESULT result;
	D3DXIMAGE_INFO _Info;
	D3DXGetImageInfoFromFile(filename, &_Info);
	_Width = _Info.Width;
	_Height = _Info.Height;
	//create the new texture by loading a bitmap image file
	result = D3DXCreateTextureFromFileEx(
		d3ddev,              //Direct3D device object
		filename,            //bitmap filename
		_Width,          //bitmap image width
		_Height,         //bitmap image height
		1,                   //mip-map levels (1 for no chain)
		0,     //the type of surface (standard)
		D3DFMT_A8R8G8B8,      //surface format (default)
		D3DPOOL_MANAGED,     //memory class for the texture
		D3DX_FILTER_NONE,        //image filter
		D3DX_FILTER_BOX,        //mip filter
		D3DCOLOR_XRGB(255, 0, 255),          //color key for transparency
		&_Info,							//bitmap file info (from loaded file)
		NULL,						//color palette
		&this->_Texture);          //destination texture
	//make sure the bitmap texture was loaded correctly
	if (result != D3D_OK)
		MessageBox(NULL, "sai duong dan len file hinh", "error Texture", MB_OK);

	_Width = _Width / _Columns;
	_Height = _Height / _Rows;
	_StartFrame = 0;
	_CurrentFrame = 0;
	_LastFrame = _Columns - 1;
	_AnimationDelay = 5;
	_AnimationCount = 0;
	alphablend = 255;
	_DeltaFlip = 0;
	Vx = 0;
	Vy = 0;
	_IsAnimationEnd = false;
	_Camera.push_back(0);

	_Id.push_back(id);
	_DirectOrder[0] = 0;
	_Flip.push_back(false);

	Box bx(-_Width / 2, -_Height / 2, _Width, _Height, 0, 0);
	_Box.push_back(bx);
	_CspriteLoad = true;
	_NonFlip = 0;
}

void CSprite::load(char* filename)
{
	load(filename, 1, 1);
}

void CSprite::load(char* filename, int id)
{
	load(filename, 1, 1, id);
}

void CSprite::addNewObject(float x, float y, int flip)
{
	_DirectOrder[0] = _Id.size();
	_Id.push_back(0);
	_Flip.push_back(flip);
	Box bx(x - _Width / 2, y - _Height / 2, _Width, _Height, 0, 0);
	D3DXVECTOR2 position;
	position.x = x;
	position.y = y;
	_Box.push_back(bx);
}

void CSprite::addNewObject(int id, float x, float y, float width, float height, int flip)
{
	_DirectOrder[id] = _Id.size();
	_Id.push_back(id);
	_Flip.push_back(flip);
	Box bx(x - width / 2, y - height / 2, width, height, 0, 0);
	_Box.push_back(bx);
	_Camera.push_back(0);

}

void CSprite::addNewObject(int id, float x, float y, int camera, int flip)
{
	_DirectOrder[id] = _Id.size();
	_Id.push_back(id);
	_Flip.push_back(flip);
	Box bx(x - _Width / 2, y - _Height / 2, _Width, _Height, 0, 0);
	_Box.push_back(bx);
	_Camera.push_back(camera);
	//_Active.push_back(false);
}

void CSprite::addNewObject(int id, int type, float x, float y, int camera, int flip)
{
	_Type.push_back(type);
	_DirectOrder[id] = _Id.size();
	_Id.push_back(id);
	_Flip.push_back(flip);
	Box bx(x - _Width / 2, y - _Height / 2, _Width, _Height, 0, 0);
	_Box.push_back(bx);
	_Camera.push_back(camera);
	//_Active.push_back(false);
}

void CSprite::animate(bool play)
{
	_AnimationPlay = play;
}

void CSprite::animate(int animationdelay, int startframe, int lastframe, int repeat)
{
	_AnimationDelay = animationdelay;
	_StartFrame = startframe;
	_LastFrame = lastframe;
	_RepeatAnimation = repeat;
}

int CSprite::getStatus(int id)
{
	return 0;
}

int CSprite::getStatus()
{
	return 0;
}

void CSprite::setStatus(int stt, int id)
{
}

void CSprite::animate(int delta)
{
	_IsAnimationEnd = false;
	if (_AnimationPlay)
	{
		if (_AnimationTick >= _AnimationDelay)
		{
			_AnimationTick = delta - _AnimationDelay;
			_AnimationCount = 0;
			if (_CurrentFrame < _StartFrame)
				_CurrentFrame = _StartFrame - 1;
			if (++_CurrentFrame > _LastFrame)
			{
				if (_RepeatAnimation)
					_CurrentFrame = _StartFrame;
				else
					_CurrentFrame -= 1;
				_IsAnimationEnd = true;
			}
		}
		else
		{
			_AnimationTick += delta;
		}
	}
}

void CSprite::animate(int animationdelay, int startframe, int lastframe)
{
	int cf = getCurrentFrame();
	if (_StartFrame != startframe)
		setCurrentFrame(startframe);
	_AnimationDelay = animationdelay;
	_StartFrame = startframe;
	_LastFrame = lastframe;
	_RepeatAnimation = true;
}

void CSprite::setSize(int width, int height)
{
	_Width = width;
	_Height = height;
}

void CSprite::setWidth(int width)
{
	_Width = width;
}

void CSprite::setHeight(int height)
{
	_Height = height;
}

void CSprite::setCamera(int camera)
{
	_Camera.at(0) = camera;
}

void CSprite::setX(float x)
{
	float delta = x - getX();
	if (delta != 0)
		_Box.at(0).x += delta;
}

void CSprite::setY(float y)
{
	float delta = y - getY();
	if (delta != 0)
		_Box.at(0).y += delta;
}

void CSprite::setX(float x, int id)
{
	int vectorPosition = findVectorPosition(id);
	if (vectorPosition)
	{
		float delta = x - getX(id);
		if (delta != 0)
			_Box.at(vectorPosition).x += delta;
	}
}

void CSprite::setY(float y, int id)
{
	int vectorPosition = findVectorPosition(id);
	if (vectorPosition)
	{
		float delta = y - getY(id);
		if (delta != 0)
			_Box.at(vectorPosition).y += delta;
	}
}

void CSprite::setLastFrame(int last)
{
	_LastFrame = last;
}

void CSprite::setCurrentFrame(int current)
{
	_CurrentFrame = current;
}

void CSprite::setAnimateDelay(int delay)
{
	_AnimationDelay = delay;
}

void CSprite::setDeltaFlip(float deltaflip)
{
	_DeltaFlip = deltaflip;
}

void CSprite::setPosition(float x, float y)
{
	setX(x);
	setY(y);
}

void CSprite::setFlip(int flip)
{
	_Flip.at(0) = flip;
}

void CSprite::setFlip(int flip, int id)
{
	int vectorPosition = findVectorPosition(id);
	if (vectorPosition)
	{
		_Flip.at(vectorPosition) = flip;
	}
}

void CSprite::setPosition(float x, float y, int id)
{
	setX(x, id);
	setY(y, id);
}

void CSprite::setNonFlip(int fliptype)
{
	_NonFlip = fliptype;
}

bool CSprite::isAnimationEnd()
{
	return _IsAnimationEnd;
}

int CSprite::isFlip()
{
	return _Flip.at(0);
}

int CSprite::isActive(int _id)
{
	return 0;
}

bool CSprite::isLoad()
{
	return _CspriteLoad;
}

int CSprite::findVectorPosition(int id)
{
	return _DirectOrder[id];
}



int CSprite::isFlip(int id)
{
	return _Flip.at(findVectorPosition(id));
}

bool CSprite::isAnimate()
{
	return _AnimationPlay;
}

void CSprite::render(int delta)
{
	for (int i = 0; i < _Box.size(); i++)
	{
		D3DXVECTOR2 TransformPosition;
		switch (_Camera.at(i))
		{
		case 0:
			TransformPosition = cmr.GetPointTransform(_Box.at(i).x + _Box.at(i).w / 2, _Box.at(i).y + _Box.at(i).h / 2);
			break;
		case 1:
			TransformPosition = cmr2.GetPointTransform(_Box.at(i).x + _Box.at(i).w / 2, _Box.at(i).y + _Box.at(i).h / 2);
			break;
		}
		switch (_NonFlip)
		{
		case 1:
			_Flip.at(i) = false;
			break;
		case 2:
			_Flip.at(i) = true;
			break;
		}
		if (_Flip.at(i))
			flip(delta, TransformPosition.x, TransformPosition.y);
		else
			draw(delta, TransformPosition.x, TransformPosition.y);
	}
}

int CSprite::render(int delta, int _id)
{
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
		switch (_NonFlip)
		{
		case 1:
			_Flip.at(temp) = false;
			break;
		case 2:
			_Flip.at(temp) = true;
			break;
		}
		if (_Flip.at(temp))
			flip(delta, TransformPosition.x, TransformPosition.y);
		else
			draw(delta, TransformPosition.x, TransformPosition.y);
		return 1;
	}
	return 0;
}

void CSprite::renderMergeObject(int delta, int _id)
{
	int temp = findVectorPosition(_id);
	if (temp)
	{
		int columns = _Box.at(temp).w / getWidth();
		int  rows = _Box.at(temp).h / getHeight();
		for (int i = 0; i < columns; i++)
			for (int j = 0; j < rows; j++)
			{
				D3DXVECTOR2 postion(_Box.at(temp).x + i * getWidth(), _Box.at(temp).y + j * getHeight());
				D3DXVECTOR2 TransformPosition;
				switch (_Camera.at(temp))
				{
				case 0:
					TransformPosition = cmr.GetPointTransform(postion.x + getWidth() / 2, postion.y + getHeight() / 2);
					break;
				case 1:
					TransformPosition = cmr2.GetPointTransform(postion.x + getWidth() / 2, postion.y + getHeight() / 2);
					break;
				}
				switch (_NonFlip)
				{
				case 1:
					_Flip.at(temp) = false;
					break;
				case 2:
					_Flip.at(temp) = true;
					break;
				}
				if (_Flip.at(temp))
					flip(delta, TransformPosition.x, TransformPosition.y);
				else
					draw(delta, TransformPosition.x, TransformPosition.y);
			}
	}
}

void CSprite::renderOne(int delta)
{
	D3DXVECTOR2 TransformPosition;
	switch (_Camera.at(0))
	{
	case 0:
		TransformPosition = cmr.GetPointTransform(getX(), getY());
		break;
	case 1:
		TransformPosition = cmr2.GetPointTransform(getX(), getY());
		break;
	}
	switch (_NonFlip)
	{
	case 1:
		_Flip.at(0) = false;
		break;
	case 2:
		_Flip.at(0) = true;
		break;
	}
	if (_Flip.at(0))
		flip(delta, TransformPosition.x, TransformPosition.y);
	else
		draw(delta, TransformPosition.x, TransformPosition.y);
}

void CSprite::renderTile(int delta)
{
	for (int i = 0; i < _Box.size(); i++)
	{
		D3DXVECTOR2 TransformPosition;
		switch (_Camera.at(i))
		{
		case 0:
			TransformPosition = cmr.GetPointTransform(_Box.at(i).x + _Box.at(i).w / 2, _Box.at(i).y + _Box.at(i).h / 2);
			break;
		case 1:
			TransformPosition = cmr2.GetPointTransform(_Box.at(i).x + _Box.at(i).w / 2, _Box.at(i).y + _Box.at(i).h / 2);
			break;
		}
		D3DXVECTOR3 position(0, 0, 0);
		D3DXVECTOR3 center(0, 0, 0);
		RECT		srcRect;
		srcRect.left = (_Type.at(i) % _Columns) *_Width;
		srcRect.top = (_Type.at(i) / _Columns) *_Height;
		srcRect.right = srcRect.left + _Width;
		srcRect.bottom = srcRect.top + _Height;
		position.x = TransformPosition.x - _Width / 2;
		position.y = TransformPosition.y - _Height / 2;
		SpriteHandler->Draw(
			this->_Texture,
			&srcRect,
			&center,
			&position,
			D3DCOLOR_ARGB(alphablend, Color.getR(), Color.getG(), Color.getB()));
	}
}

void CSprite::renderTile(int delta, int id)
{
	int temp = findVectorPosition(id);
	D3DXVECTOR2 TransformPosition;

	TransformPosition = cmr.GetPointTransform(_Box.at(temp).x + _Box.at(temp).w / 2, _Box.at(temp).y + _Box.at(temp).h / 2);
	//ep kieu de chong loi float, giup background khoi bi nhap nhay
	TransformPosition.x = (int)TransformPosition.x;
	TransformPosition.y = (int)TransformPosition.y;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	RECT		srcRect;
	srcRect.left = (_Type.at(temp) % _Columns) *_Width;
	srcRect.top = (_Type.at(temp) / _Columns) *_Height;
	srcRect.right = srcRect.left + _Width;
	srcRect.bottom = srcRect.top + _Height;
	position.x = TransformPosition.x - _Width / 2;
	position.y = TransformPosition.y - _Height / 2;
	SpriteHandler->Draw(
		this->_Texture,
		&srcRect,
		&center,
		&position,
		D3DCOLOR_ARGB(alphablend, Color.getR(), Color.getG(), Color.getB()));
}

int CSprite::readPixel(int x, int y)
{
	//0->Blue, 1->Green, 2->Red, 3->Alpha
	DWORD* dummy = (DWORD*)_LockRect.pBits;
	return dummy[y*_LockRect.Pitch / sizeof(DWORD) + x];
}

CColor CSprite::readPixelARGB(int x, int y)
{
	CColor temp;
	//D3DLOCKED_RECT locked;
	//HRESULT hr = _Texture->LockRect(0, &locked, NULL, 0);
	BYTE *bytePointer = (BYTE*)_LockRect.pBits;
	DWORD index = (x * 4 + (y*(_LockRect.Pitch)));
	// Blue
	temp.setB(bytePointer[index]);

	// Green
	temp.setG(bytePointer[index + 1]);

	// Red
	temp.setR(bytePointer[index + 2]);

	// Alpha
	temp.setA(bytePointer[index + 3]);

	return temp;

}

int CSprite::saveTexture(vector<int> temp, char* filepath)
{
	int rows = 4;
	int columns = 0;
	if (temp.size() % rows > 0)
		columns = (temp.size() / rows) + 1;
	else
		columns = (temp.size() / rows);

	D3DLOCKED_RECT lockedRect;
	LPDIRECT3DTEXTURE9 tex;
	D3DXCreateTexture(d3ddev, columns * _Width, _Height * rows, 1, D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &tex);
	tex->LockRect(0, &lockedRect, NULL, 0);
	BYTE *bytePointer = (BYTE*)lockedRect.pBits;
	for (int i = 0; i < temp.size(); i++)
	{
		int miny = (int)(i / columns) * _Height;
		int maxy = ((int)(i / columns) + 1) * _Height;
		for (long y = miny; y < maxy; y++)
		{
			int minx = (i % columns) * _Width;
			int maxx = ((i % columns) + 1) * _Width;

			for (long x = minx; x < maxx; x++)
			{
				long index = (x * 4 + (y * lockedRect.Pitch));
				int dx = (x - (i % columns)* _Width);
				int xxx = (temp.at(i) % _Columns * _Width) + dx;
				int dy = y - ((int)(i / columns)) * _Height;
				int yyy = ((int)(temp.at(i) / _Columns) *_Height) + dy;

				CColor color = readPixelARGB(xxx, yyy);
				// Blue
				bytePointer[index] = color.getB();

				// Green
				bytePointer[index + 1] = color.getG();

				// Red
				bytePointer[index + 2] = color.getR();

				// Alpha
				bytePointer[index + 3] = color.getA();
			}
		}
	}
	tex->UnlockRect(0);
	HRESULT hr = D3DXSaveTextureToFileA(filepath, D3DXIFF_PNG, tex, 0);
	tex->Release();
	if (hr != D3D_OK)
		return 0;
	return 1;
}

int CSprite::compareTwoTile(int first, int second)
{
	int firstleft = (first % _Columns) * _Width;
	int secondleft = (second % _Columns) * _Width;
	int firstright = firstleft + _Width;
	int secondright = secondleft + _Width;
	int firsttop = (first / _Columns) * _Height;
	int secondtop = (second / _Columns) * _Height;
	int firstbot = firsttop + _Height;
	int secondbot = secondtop + _Height;

	int i, j, k, l;
	for (i = firstleft, j = secondleft; i < firstright, j < secondright; i++, j++)
	{
		for (k = firsttop, l = secondtop; k < firstbot, l < secondbot; k++, l++)
		{
			int y = readPixel(j, l);
			int x = readPixel(i, k);
			if (x != y)
				return 0;
		}
	}
	return 1;
}

void CSprite::draw(int delta, float x, float y)
{

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	RECT		srcRect;
	srcRect.left = (_CurrentFrame % _Columns) *_Width;
	srcRect.top = (_CurrentFrame / _Columns) * _Height;
	srcRect.right = srcRect.left + _Width;
	srcRect.bottom = srcRect.top + _Height;
	position.x = x - _Width / 2;
	position.y = y - _Height / 2;
	SpriteHandler->Draw(
		this->_Texture,
		&srcRect,
		&center,
		&position,
		D3DCOLOR_ARGB(Color.getA(), Color.getR(), Color.getG(), Color.getB()));
}

void CSprite::flip(int delta, float x, float y)
{
	D3DXMATRIX		oldMt;
	SpriteHandler->GetTransform(&oldMt);
	D3DXMATRIX		newMt;
	D3DXVECTOR2		center = D3DXVECTOR2((x + _Width / 2), (y + _Height / 2));
	D3DXVECTOR2		rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX		finalMt = newMt * oldMt;
	SpriteHandler->SetTransform(&finalMt);

	float temp = x;						// Luu tru vi tri thuc te
	x += _Width + _DeltaFlip;
	this->draw(delta, x, y);
	SpriteHandler->SetTransform(&oldMt);			// Tra lai gia tri ma tran ban dau neu khong thi sprite se bi lat lien tuc
}

int CSprite::getType(int id)
{
	int temp = findVectorPosition(id);
	return _Type.at(temp);
}

int CSprite::getRows()
{
	return _Rows;
}

int CSprite::getColumns()
{
	return _Columns;
}

Box CSprite::getBox()
{
	return _Box.at(0);
}

Box CSprite::getBox(int id)
{
	return _Box.at(findVectorPosition(id));
}

int CSprite::getCamera()
{
	return _Camera.at(0);
}

void CSprite::getObject(Box)
{
}

void CSprite::tranferX(float deltaX)
{
	_Box.at(0).x += deltaX;
}

void CSprite::tranferY(float deltaY)
{
	_Box.at(0).y += deltaY;
}

void CSprite::moveX(int deltaX)
{
	if (deltaX < 0)
	{
		_Flip.at(0) = false;
	}
	else
		if (deltaX > 0)
			_Flip.at(0) = true;
	Vx = deltaX * 0.15;
	_Box.at(0).vx = Vx;
	_Box.at(0).x += Vx;
	Vx = 0;
}

void CSprite::moveX(int deltaX, int id)
{
	int vectorposition = findVectorPosition(id);
	if (deltaX < 0)
	{
		_Flip.at(vectorposition) = false;
	}
	else
		if (deltaX > 0)
			_Flip.at(vectorposition) = true;
	Vx = deltaX * 0.15;
	_Box.at(vectorposition).vx = Vx;
	_Box.at(vectorposition).x += Vx;
	Vx = 0;
}

void CSprite::moveY(int deltaY)
{
	Vy = deltaY * 0.15f;
	_Box.at(0).vy = Vy;
	_Box.at(0).y += Vy;
	Vy = 0;
}

void CSprite::moveY(int deltaY, int id)
{
	int vectorposition = findVectorPosition(id);
	Vy = deltaY * 0.15f;
	_Box.at(vectorposition).vy = Vy;
	_Box.at(vectorposition).y += Vy;
	Vy = 0;
}

void CSprite::move(float deltax, float deltay)
{
	_Box.at(0).x += deltax;
	_Box.at(0).y += deltay;
}

float CSprite::getX()
{
	return _Box.at(0).x + _Box.at(0).w / 2;
}

float CSprite::getX(int id)
{
	int position = findVectorPosition(id);
	return _Box.at(position).x + _Box.at(findVectorPosition(id)).w / 2;
}

float CSprite::getY()
{
	return _Box.at(0).y + _Box.at(0).h / 2;
}

float CSprite::getY(int id)
{
	return	_Box.at(findVectorPosition(id)).y + _Box.at(findVectorPosition(id)).h / 2;
}

float CSprite::getWidth()
{
	return _Width;
}

float CSprite::getHeight()
{
	return _Height;
}

int CSprite::getCurrentFrame()
{
	return _CurrentFrame;
}

vector<Box> CSprite::getVectorBox()
{
	return _Box;
}

vector<Box> CSprite::getVectorBox(int first, int last)
{
	if (last >= _Box.size())
		last = _Box.size() - 1;
	vector<Box> temp;
	for (int i = first; i <= last; i++)
		temp.push_back(_Box.at(i));
	return temp;
}

int CSprite::manualFind(int id)
{
	for (int i = 0; i < _Id.size(); i++)
	{
		if (id == _Id.at(i))
			return i;
	}
	return 0;
}

void CSprite::setId(int oldId, int newId)
{
	int vectorposition = manualFind(oldId);
	if (vectorposition)
	{
		_DirectOrder.erase(oldId);
		_DirectOrder[newId] = vectorposition;
		_Id.at(vectorposition) = newId;
	}
}

void CSprite::Delete(int _id)
{
	int vectorposition = findVectorPosition(_id);
	if (vectorposition)
	{
		_DirectOrder.erase(_id);
		_Box.erase(_Box.begin() + vectorposition);
		_Flip.erase(_Flip.begin() + vectorposition);
		_Id.erase(_Id.begin() + vectorposition);
		_Type.erase(_Type.begin() + vectorposition);
	}
}

void CSprite::Clear()
{
	while (_Box.size() > 1)
	{
		_DirectOrder.erase(_Id.at(1));
		_Box.erase(_Box.begin() + 1);
		_Flip.erase(_Flip.begin() + 1);
		_Id.erase(_Id.begin() + 1);
		_Type.erase(_Type.begin() + 1);
	}
}

void CSprite::ClearAll()
{
	_Box.clear();
	_Flip.clear();
	_Id.clear();
	_DirectOrder.clear();
	_Type.clear();
}

void CSprite::specificrenderforsimon(float x, float y, float width)
{
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	RECT		srcRect;
	if (!_Flip.at(0))
	{
		srcRect.left = (_CurrentFrame % _Columns) * _Width;
		srcRect.right = srcRect.left + width;
	}
	else
	{
		srcRect.left = (_CurrentFrame % _Columns) * _Width + (_Width - width);
		srcRect.right = (_CurrentFrame % _Columns) * _Width + _Width;
	}
	srcRect.top = (_CurrentFrame / _Columns) * _Height;

	srcRect.bottom = srcRect.top + _Height;
	position.x = x - _Width / 2;
	position.y = y - _Height / 2;
	SpriteHandler->Draw(
		this->_Texture,
		&srcRect,
		&center,
		&position,
		D3DCOLOR_ARGB(alphablend, Color.getR(), Color.getG(), Color.getB()));
}

void CSprite::specificfliprenderforsimon(float x, float y, float width)
{
	D3DXMATRIX		oldMt;
	SpriteHandler->GetTransform(&oldMt);
	D3DXMATRIX		newMt;
	D3DXVECTOR2		center = D3DXVECTOR2((x + width / 2), (y + _Height / 2));
	D3DXVECTOR2		rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX		finalMt = newMt * oldMt;
	SpriteHandler->SetTransform(&finalMt);

	float temp = x;						// Luu tru vi tri thuc te
	x += width + _DeltaFlip;
	this->specificrenderforsimon(x, y, width);
	SpriteHandler->SetTransform(&oldMt);			// Tra lai gia tri ma tran ban dau neu khong thi sprite se bi lat lien tuc
}

void CSprite::update(int delta)
{
}

void CSprite::update(int delta, int id)
{
}

void CSprite::update(int delta, Box bx, int id)
{

}

int CSprite::getHealth()
{
	return 0;
}


CColor::CColor(int a, int r, int g, int b)
{
	_a = a;
	_r = r;
	_g = g;
	_b = b;
}

CColor::CColor()
{
	_a = 255;
	_r = 255;
	_g = 255;
	_b = 255;
}

CColor::~CColor()
{
}

int CColor::getB()
{
	return _b;
}

int CColor::getG()
{
	return _g;
}

int CColor::getR()
{
	return _r;
}

int CColor::getA()
{
	return _a;
}

void CColor::setARGB(int a, int r, int g, int b)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

void CColor::setR(int x)
{
	_r = x;
}

void CColor::setG(int y)
{
	_g = y;
}

void CColor::setB(int z)
{
	_b = z;
}

void CColor::setA(int a)
{
	_a = a;
}

CGameObject::CGameObject()
{
	_x = 0;
	_y = 0;
}

CGameObject::~CGameObject()
{
}

float CGameObject::getX()
{
	return _x;
}

float CGameObject::getY()
{
	return _y;
}

void CGameObject::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void CGameObject::setX(int x)
{
	_x = x;
}

void CGameObject::setY(int y)
{
	_y = y;
}

CColor CColor::operator=(const CColor&  other)
{
	return CColor(other._a, other._r, other._g, other._b);
}
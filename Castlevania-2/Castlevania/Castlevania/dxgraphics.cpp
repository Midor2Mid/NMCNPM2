// Beginning Game Programming, Second Edition
// dxgraphics.cpp - Direct3D framework source code file

#include <d3d9.h>
#include <d3dx9.h>
#include "dxgraphics.h"
//variable declarations
LPDIRECT3D9			d3d			=	NULL;
LPDIRECT3DDEVICE9	d3ddev		=	NULL;
LPDIRECT3DSURFACE9	backbuffer	=	NULL;
LPDIRECT3DSURFACE9	surface		=	NULL;

int Init_Direct3D(HWND hwnd, int width, int height, int fullscreen)
{
    //initialize Direct3D
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (d3d == NULL)
    {
        MessageBox(hwnd, "Error initializing Direct3D", "Error", MB_OK);
        return 0;
    }

    //set Direct3D presentation parameters
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = width;
    d3dpp.BackBufferHeight = height;

    //create Direct3D device
    d3d->CreateDevice(
        D3DADAPTER_DEFAULT, 
        D3DDEVTYPE_HAL, 
        hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, 
        &d3ddev);

    if (d3ddev == NULL)
    {
        MessageBox(hwnd, "Error creating Direct3D device", "Error", MB_OK);
        return 0;
    }

    //clear the backbuffer to black
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
    //create pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(
		515,					//width of the surface
        450,					//height of the surface
        D3DFMT_X8R8G8B8,    //surface format
        D3DPOOL_DEFAULT,    //memory pool to use
        &surface,           //pointer to the surface
        NULL);              //reserved (always NULL)
    return 1;
}

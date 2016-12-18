#include "dxinput.h"

LPDIRECTINPUT8			dinput;
LPDIRECTINPUTDEVICE8	dikeyboard;
LPDIRECTINPUTDEVICE8	dimouse;
DIMOUSESTATE			mousesate;

BYTE  _KeyStates[256];
DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
int Init_DirectInput(HWND hWnd)
{
	HRESULT result;
	result = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);
	if (result != DI_OK)
	{
		MessageBox(NULL, "loi tao Directinput", "loi ham DirectInputCreate8", MB_OK);
		return 0;
	}

	result = dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
	if (result != DI_OK)
		return 0;
	dinput->CreateDevice(GUID_SysKeyboard,
		&dikeyboard,
		NULL);
	return 1;

}
int Init_Keyboard(HWND hWnd)
{
	HRESULT result;
	result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);

	result = dikeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	dikeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	result = dikeyboard->Acquire();
	return  1;
}

void Poll_Keyboard()
{

	HRESULT hr = dikeyboard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
	if (hr != S_OK)
	{
		hr = dikeyboard->Acquire();
		dikeyboard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
	}
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = dikeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);
	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

int	Key_Down(int key)
{
	return (_KeyStates[key] & 0x80);
}


void Kill_Keyboard()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL();
	}
}

int Init_Mouse(HWND hWnd)
{
	HRESULT result;
	result = dimouse->SetDataFormat(&c_dfDIMouse);

	if (result != DI_OK)
	{
		MessageBox(NULL, "Khong the SetdataFormat cho Mouse", "Loi InitMouse", MB_OK);
		return 0;
	}
	result = dimouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

	if (result != DI_OK)
	{
		MessageBox(NULL, "Khong the SetCooperativelevel cho Mouse", "Loi InitMouse", MB_OK);
		return 0;
	}
	result = dimouse->Acquire();

	if (result != DI_OK)
	{
		MessageBox(NULL, "Khong the Acquire Mouse", "Loi InitMouse", MB_OK);
		return 0;
	}
	return 1;
}

int Mouse_Button(int Buttons)
{
	return BUTTON_DOWN(mousesate, Buttons);
}

void Poll_Mouse()
{
	HRESULT hr = dimouse->GetDeviceState(sizeof(mousesate), (LPVOID)&mousesate);
	if (hr != S_OK)
	{
		dimouse->Acquire();
		dimouse->GetDeviceState(sizeof(mousesate), (LPVOID)&mousesate);
	}
}

int Mouse_X()
{
	return mousesate.lX;
}

int Mouse_Y()
{
	return mousesate.lY;
}

void Kill_Mouse()
{
	if (dimouse != NULL)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}
}
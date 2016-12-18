#ifndef _DXINPUT_H
#define _DXINPUT_H

#define BUTTON_DOWN(obj,button) (obj.rgbButtons[button]&0x80)

#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE	1024

#include <dinput.h>

int OnKeyDown(int KeyCode);
int OnKeyUp(int KeyCode);
void Poll_Keyboard();
int Init_DirectInput(HWND);
int Init_Keyboard(HWND);
void Kill_Keyboard();
int Init_Mouse(HWND);
void Poll_Mouse();
void Kill_Mouse();
int Mouse_Button(int);
int Mouse_X();
int Mouse_Y();
int Key_Down(int);

extern BYTE  _KeyStates[256];
extern DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];

extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dikeyboard;

#endif // !_DXINPUT_H

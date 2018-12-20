#ifndef _INPUT_H
#define _INPUT_H

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

class Input
{
public:
	Input();
	~Input();

	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	bool Update();

	bool IsKeyDown(unsigned int key);
	bool IsKeyUp(unsigned int key);
	bool IsKeyHit(unsigned int key);

private:
	const static int numKeys = 256;

	bool ReadKeyboard();

	IDirectInput8 *directInput;
	IDirectInputDevice8 *keyboard;

	bool keys[numKeys];
	bool prevKeys[numKeys];
};

#endif
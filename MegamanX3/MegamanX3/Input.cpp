#include "Input.h"
#include "pch.h"

Input::Input(void)
{
	directInput = 0;
	keyboard = 0;
	memset(keys, 0, sizeof(bool)*numKeys);
}

Input::~Input(void)
{
	if (keyboard)
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = 0;
	}

	if (directInput)
	{
		directInput->Release();
		directInput = 0;
	}
}

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result;

	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool Input::Update()
{
	memcpy(prevKeys, keys, sizeof(bool) * numKeys);

	bool result;

	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	return true;
}

bool Input::IsKeyDown(unsigned int key)
{
	return keys[key];
}

bool Input::IsKeyHit(unsigned int key)
{
	return keys[key] && !prevKeys[key];
}

bool Input::ReadKeyboard()
{
	HRESULT result;

	result = keyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

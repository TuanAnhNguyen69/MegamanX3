#ifndef _FRAMEWORK_H
#define _FRAMEWORK_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "Engine.h"

class FrameWork
{
public:
	FrameWork();
	~FrameWork();

	bool Initialize(GameComponent *gameComponent);
	void Run();

private:
	bool CreateDxWindow(char* windowTitle, int x, int y, int width, int height);
	
	char *applicationName;
	HINSTANCE instance;
};

#endif

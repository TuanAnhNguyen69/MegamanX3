#include "pch.h"
#include "FrameWork.h"
#include "GameScene.h"

int main()
{
	FrameWork *framework = new FrameWork();
	if (framework->Initialize(new GameScene())) {
		framework->Run();
	}
	delete framework;
	return 0;
}

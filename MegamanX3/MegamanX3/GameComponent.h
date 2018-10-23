#ifndef _GAME_COMPONENT_H
#define _GAME_COMPONENT_H

class GameComponent
{
public:
	GameComponent() {}
	virtual ~GameComponent() {}

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

#endif
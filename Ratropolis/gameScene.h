#pragma once
#include "Scene.h"

#define MAPWIDTH	8000
#define MAPHEIGHT	1500

class Card;

class gameScene : public Scene
{
private:

public:
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();
};


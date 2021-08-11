#pragma once
#include "Scene.h"

class Player;
class Card;

#define MAPWIDTH	8000
#define MAPHEIGHT	1500

class testGameScene : public Scene
{
private:
	Player* _player;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();

	void setBackImage();
	void drawBackImage();
};


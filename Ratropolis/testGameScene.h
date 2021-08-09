#pragma once
#include "Scene.h"

class Card;

#define MAPWIDTH	8000
#define MAPHEIGHT	1500

class testGameScene : public Scene
{
private:
	float _x, _y;
	Card* _sample;

public:
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();

	void setBackImage();
	void drawBackImage();
};


#pragma once
#include "Scene.h"

class sampleScene : public Scene
{
public:
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();
};


#pragma once
#include "Scene.h"

class sampleScene : public Scene
{

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();
};


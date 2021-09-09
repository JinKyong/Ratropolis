#pragma once
#include "Scene.h"

#define MAPWIDTH	8000
#define MAPHEIGHT	1500

class loadingScene : public Scene
{
private:
	WCHAR _text[128];

	float _count;
	int _number;

public:
	bool _change;

	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();
	
	void drawBackImage();

	static DWORD CALLBACK loadingData(LPVOID lpParameter);
};


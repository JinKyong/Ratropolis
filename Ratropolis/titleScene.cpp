#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init(Player* player)
{
	_player = player;

	//CAMERAMANAGER->setFade(FADEOUT);
	CAMERAMANAGER->setBackScreenSize(WINSIZEX, WINSIZEY);

	STREAMMANAGER->startVideo("title");

	_change = false;

	return S_OK;
}

void titleScene::release()
{
	STREAMMANAGER->closeVideo();
}

void titleScene::update()
{
	if (STREAMMANAGER->getPosition() >= STREAMMANAGER->getLength()) {
		STREAMMANAGER->closeVideo();
		CAMERAMANAGER->setFade(FADEOUT);
		_change = true;		
	}

	changeScene();
}

void titleScene::render()
{
}

void titleScene::changeScene()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		STREAMMANAGER->closeVideo();
		CAMERAMANAGER->setFade(FADEOUT);
		_change = true;
	}

	if (_change) {
		if (CAMERAMANAGER->getAlpha() == 1.0)
			SCENEMANAGER->changeScene("sample");
	}
}

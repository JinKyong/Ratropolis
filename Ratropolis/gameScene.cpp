#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init(Player * player)
{
	Scene::init(player);

	CAMERAMANAGER->setBackScreenSize(MAPWIDTH, MAPHEIGHT);


	DECKMANAGER->init();
	GAMEMANAGER->playGame();

	return S_OK;
}

void gameScene::release()
{
	COLLISIONMANAGER->release();
	COLLISIONMANAGER->releaseSingleton();

	DECKMANAGER->release();
	DECKMANAGER->releaseSingleton();
}

void gameScene::update()
{
	if (!UIMANAGER->getOpen()) {
		DECKMANAGER->update();
		GAMEMANAGER->update();
		CAMERAMANAGER->updateScreen(_player->getCamX(), _player->getCamY());
	}

	UIMANAGER->update();
}

void gameScene::render()
{
	if (PRINTMANAGER->isDebug()) {
		//WCHAR tmp[128];


	}

	DECKMANAGER->render();
	GAMEMANAGER->render();
	UIMANAGER->render();
}

void gameScene::changeScene()
{
}

#include "stdafx.h"
#include "testGameScene.h"
#include "Player.h"

HRESULT testGameScene::init()
{
	CAMERAMANAGER->setBackScreenSize(MAPWIDTH, MAPHEIGHT);
	COLLISIONMANAGER->init();

	_player = GAMEMANAGER->getPlayer();
	_player->setCamX(MAPWIDTH / 2);
	_player->setCamY(MAPHEIGHT - 240);
	_player->playGame();

	//배경 이미지 등록하고 한번만 그림
	setBackImage();
	drawBackImage();

	DECKMANAGER->init();
	GAMEMANAGER->playGame();
	UIMANAGER->playGame();

	return S_OK;
}

void testGameScene::release()
{
	COLLISIONMANAGER->release();
	COLLISIONMANAGER->releaseSingleton();

	DECKMANAGER->release();
	DECKMANAGER->releaseSingleton();
}

void testGameScene::update()
{
	if (!UIMANAGER->getOpen()) {
		DECKMANAGER->update();
		GAMEMANAGER->update();
		CAMERAMANAGER->updateScreen(_player->getCamX(), _player->getCamY());
	}

	UIMANAGER->update();
}

void testGameScene::render()
{
	if (PRINTMANAGER->isDebug()) {
		//WCHAR tmp[128];


	}

	DECKMANAGER->render();
	GAMEMANAGER->render();
	UIMANAGER->render();

}

void testGameScene::changeScene()
{
}

void testGameScene::setBackImage()
{
	for (int i = 0; i < 5; i++) {
		char key[128];
		WCHAR tmp[128];

		sprintf_s(key, "Landscape_Desert_%d", i);
		swprintf_s(tmp, L"img/background/Landscape_Desert_%d.png", i);
		IMAGEMANAGER->addDImage(key, tmp, 2000, 949);

		sprintf_s(key, "Landscape_NearDesert_%d", i);
		swprintf_s(tmp, L"img/background/Landscape_NearDesert_%d.png", i);
		IMAGEMANAGER->addDImage(key, tmp, 1000, 709);
	}

	IMAGEMANAGER->addDImage("desertTile", L"img/background/DesertTile.png", 60, 60);
	IMAGEMANAGER->addDImage("waterTile", L"img/background/water.png", 60, 60);
}

void testGameScene::drawBackImage()
{
	//배경 그리기
	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_STATIC);

	DTDMANAGER->beginDraw();

	//back
	for (int i = 0; i < 5; i++) {
		char key[128];

		sprintf_s(key, "Landscape_Desert_%d", i);
		if(i != 2)
			IMAGEMANAGER->findDImage(key)->render(2000 * i - 1000, MAPHEIGHT - 949);
		else
			IMAGEMANAGER->findDImage(key)->render(2000 * i - 1000, MAPHEIGHT - 949 - 30);

	}
	//near
	for (int i = 0; i < 5; i++) {
		char key[128];

		sprintf_s(key, "Landscape_NearDesert_%d", i);
		IMAGEMANAGER->findDImage(key)->render(1000 * i - 1000, MAPHEIGHT - 709);
		IMAGEMANAGER->findDImage(key)->render(1000 * i + 3997, MAPHEIGHT - 709);
	}


	for (int i = 0; i < MAPWIDTH; i += 60) {
		IMAGEMANAGER->findDImage("desertTile")->render(i, MAPHEIGHT - 300);
		IMAGEMANAGER->findDImage("waterTile")->render(i, MAPHEIGHT - 240, 0.25);
		IMAGEMANAGER->findDImage("waterTile")->render(i, MAPHEIGHT - 180, 0.25);
		IMAGEMANAGER->findDImage("waterTile")->render(i, MAPHEIGHT - 120, 0.25);
		IMAGEMANAGER->findDImage("waterTile")->render(i, MAPHEIGHT - 60, 0.25);
	}

	DTDMANAGER->endDraw();

	DTDMANAGER->changeRenderTargetPast();
}

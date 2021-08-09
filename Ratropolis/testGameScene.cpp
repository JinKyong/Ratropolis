#include "stdafx.h"
#include "testGameScene.h"
#include "Player.h"
#include "Cheeze.h"

HRESULT testGameScene::init(Player * player)
{
	Scene::init(player);

	CAMERAMANAGER->setBackScreenSize(MAPWIDTH, MAPHEIGHT);

	_player->setCamX(MAPWIDTH / 2);
	_player->setCamY(MAPHEIGHT - 240);
	_player->playGame();

	_sample = new Cheeze;
	_sample->init();

	//��� �̹��� ����ϰ� �ѹ��� �׸�
	setBackImage();
	drawBackImage();

	DECKMANAGER->init();
	UIMANAGER->playGame();

	return S_OK;
}

void testGameScene::release()
{
	DECKMANAGER->release();
	DECKMANAGER->releaseSingleton();
}

void testGameScene::update()
{
	_player->update();
	UIMANAGER->update();
	CAMERAMANAGER->updateScreen(_player->getCamX(), _player->getCamY());
	DECKMANAGER->update();
}

void testGameScene::render()
{
	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];

		swprintf_s(tmp, L"x : %f", _x);
		DTDMANAGER->printText(tmp, _x, _y - 40, 100, 50);

		swprintf_s(tmp, L"y : %f", _y);
		DTDMANAGER->printText(tmp, _x, _y - 20, 100, 50);

	}

	//_sample->render();
	UIMANAGER->render();
	DECKMANAGER->render();
	_player->render();
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
	//��� �׸���
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

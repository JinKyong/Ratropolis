#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(Player * player)
{
	Scene::init(player);

	swprintf_s(_text, L"");

	_count = 0;
	_number = 0;

	CreateThread(
		NULL,			//스레드의 보안속성(자신윈도우가 존재할때)
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드)
		loadingData,	//사용할 함수
		this,			//스레드 매개변수(this로 뒀으니 본 클래스)
		true,			//스레드 특성(기다릴지 바로실행할지(NULL))
		NULL			//스레드 생성 후 스레드의 ID 넘겨줌
	);

	return S_OK;
}

void loadingScene::release()
{
	drawBackImage();
}

void loadingScene::update()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.33) {
		ZeroMemory(_text, sizeof(_text));

		_number++;
		if (_number > 3)
			_number = 0;

		for(int i=0; i<_number; i++)
			lstrcatW(_text, L".");

		_count = 0;
	}

	changeScene();
}

void loadingScene::render()
{
	WCHAR text[128];
	swprintf_s(text, L"LOADING");
	lstrcatW(text, _text);

	DTDMANAGER->printText(text, WINSIZEX / 2, WINSIZEY / 2, 500, 200, 80, true, true);
}

void loadingScene::changeScene()
{
	if (_change) {
		if (CAMERAMANAGER->getAlpha() == 1.0)
			SCENEMANAGER->changeScene("game");
	}
}

void loadingScene::drawBackImage()
{
	//배경 그리기
	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_STATIC);

	DTDMANAGER->beginDraw();

	//back
	for (int i = 0; i < 5; i++) {
		char key[128];

		sprintf_s(key, "Landscape_Desert_%d", i);
		if (i != 2)
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

	dImage* worldTree = IMAGEMANAGER->findDImage("desert_worldTree");
	worldTree->render(MAPWIDTH / 2 - worldTree->getWidth() / 2, 0);

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

DWORD loadingScene::loadingData(LPVOID lpParameter)
{
	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	COLLISIONMANAGER->init();

	//배경 이미지 등록
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

	IMAGEMANAGER->addDImage("desert_worldTree", L"img/background/Desert_WorldTree.png", 2458, 1200);

	IMAGEMANAGER->addDImage("desertTile", L"img/background/DesertTile.png", 60, 60);
	IMAGEMANAGER->addDImage("waterTile", L"img/background/water.png", 60, 60);


	UIMANAGER->playGame();



	Sleep(1000);


	loadingHelper->_change = true;
	CAMERAMANAGER->setFade(FADEOUT);

	return 0;
}

#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"

HRESULT GameManager::init(Player * player)
{
	_fadeImage = IMAGEMANAGER->addDImage("fade_B", L"img/fade_B.png", WINSIZEX, WINSIZEY);

	_player = player;
	
	_buildManager = new BuildManager;
	_NPCManager = new NPCManager;

	return S_OK;
}

void GameManager::release()
{
	_buildManager->release();
	_NPCManager->release();
}

void GameManager::update()
{
	_buildManager->update();
	_NPCManager->update();

	_player->update();
}

void GameManager::render()
{
	_buildManager->render();
	_NPCManager->render();


	//배경 시야
	renderSight();

	renderPlayer();
}

void GameManager::playGame()
{
	_useBox = RectMakeCenter(WINSIZEX / 2, (WINSIZEY - 240) / 2, WINSIZEX, WINSIZEY - 360);

	_player->setCamX(44 * 90);
	_player->setCamY(CAMERAMANAGER->getBackScreenHeight() / 2 + 300);

	_buildManager->init(88);
	_NPCManager->init();
}

void GameManager::renderSight()
{
	int left = _player->getMaxLeft();
	int right = _player->getMaxRight();
	float width = CAMERAMANAGER->getBackScreenWidth();
	float height = CAMERAMANAGER->getBackScreenHeight();
	D2D1_RECT_F tmpRECT, tmpRECT2;
	float alpha;
	tmpRECT2 = dRectMake(0, 0, _fadeImage->getWidth(), _fadeImage->getHeight());

	//left
	alpha = 1;
	tmpRECT = dRectMake(left - 630, 0, 630 + 180, height);
	_fadeImage->render(tmpRECT, tmpRECT2, alpha);
	for (int i = 1; i <= 100; i++) {
		tmpRECT = dRectMake(tmpRECT.right, tmpRECT.top, 2, height);
		_fadeImage->render(tmpRECT, tmpRECT2, alpha);
		alpha -= 0.01;
	}

	//right
	alpha = 1;
	tmpRECT = dRectMake(right - 180, 0, 630 + 180, height);
	_fadeImage->render(tmpRECT, tmpRECT2, alpha);
	for (int i = 1; i <= 100; i++) {
		tmpRECT = dRectMake(tmpRECT.left - 2, tmpRECT.top, 2, height);
		_fadeImage->render(tmpRECT, tmpRECT2, alpha);
		alpha -= 0.01;
	}
}

void GameManager::renderPlayer()
{
	if (UIMANAGER->getOpen()) return;

	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_CARD);

	DTDMANAGER->beginDraw(false);

	_player->render();

	if (PRINTMANAGER->isDebug()) {
		DTDMANAGER->Rectangle(_useBox);
	}

	DTDMANAGER->endDraw();

	DTDMANAGER->changeRenderTargetPast();
}

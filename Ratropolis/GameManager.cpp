#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "BuildingHeader.h"

HRESULT GameManager::init(Player * player)
{
	_player = player;
	
	_buildManager = new BuildManager;

	return S_OK;
}

void GameManager::release()
{
}

void GameManager::update()
{
	_buildManager->update();

	_player->update();
}

void GameManager::render()
{
	_buildManager->render();

	renderPlayer();

}

void GameManager::playGame()
{
	_useBox = RectMakeCenter(WINSIZEX / 2, (WINSIZEY - 240) / 2, WINSIZEX, WINSIZEY - 360);

	_player->setCamX(44 * 90);
	_player->setCamY(CAMERAMANAGER->getBackScreenHeight() / 2 + 300);

	_buildManager->init();
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

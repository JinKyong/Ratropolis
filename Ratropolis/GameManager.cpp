#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"

HRESULT GameManager::init(Player * player)
{
	_player = player;

	return S_OK;
}

void GameManager::release()
{
}

void GameManager::update()
{
	_player->update();
}

void GameManager::render()
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

void GameManager::playGame()
{
	_useBox = RectMakeCenter(WINSIZEX / 2, (WINSIZEY - 240) / 2, WINSIZEX, WINSIZEY - 360);
}

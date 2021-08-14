#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "BuildingHeader.h"

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
	_building = _buildings.begin();
	for (; _building != _buildings.end();) {
		(*_building)->update();
		++_building;
	}

	_player->update();
}

void GameManager::render()
{
	_building = _buildings.begin();
	for (; _building != _buildings.end();) {
		(*_building)->render();
		++_building;
	}

	renderPlayer();

}

void GameManager::playGame()
{
	_useBox = RectMakeCenter(WINSIZEX / 2, (WINSIZEY - 240) / 2, WINSIZEX, WINSIZEY - 360);

	_player->setCamX(44 * 90);
	_player->setCamY(CAMERAMANAGER->getBackScreenHeight() / 2 + 300);

	_buildings.push_back(new CityHall);
	_buildings.push_back(new Building3);
	_buildings.push_back(new Building3);
	_buildings.push_back(new Building3);
	_buildings.push_back(new Building3);
	
	_buildings[0]->init(42);
	_buildings[1]->init(41);
	_buildings[2]->init(40);
	_buildings[3]->init(46);
	_buildings[4]->init(47);

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

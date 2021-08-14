#include "stdafx.h"
#include "BuildManager.h"
#include "Player.h"

HRESULT BuildManager::init()
{
	addBuilding(42, 0);
	addBuilding(41, 3);
	addBuilding(40, 3);
	addBuilding(46, 3);
	addBuilding(47, 3);

	_cursor = GAMEMANAGER->getPlayer()->getCursor();

	return S_OK;
}

void BuildManager::release()
{
}

void BuildManager::update()
{
	buildIter building = _buildings.begin();
	for (; building != _buildings.end();) {
		(*building)->update();
		++building;
	}

}

void BuildManager::render()
{
	buildIter building = _buildings.begin();
	for (; building != _buildings.end(); ++building) {
		(*building)->render();
		COLLISIONMANAGER->buildingsWithCursor(*building, _cursor->getBackX(), _cursor->getBackY());
	}

}

Building * BuildManager::addBuilding(int idX, int num, int level)
{
	Building* building = DICTIONARY->makeBuilding(num, level);

	//제대로 못불러왔으면 NULL
	if (!building) return building;

	building->init(idX);
	_buildings.push_back(building);

	return building;
}

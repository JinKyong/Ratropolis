#include "stdafx.h"
#include "BuildManager.h"
#include "Player.h"

HRESULT BuildManager::init()
{
	addBuilding(42, 0);

	_cursor = GAMEMANAGER->getPlayer()->getCursor();

	return S_OK;
}

HRESULT BuildManager::init(int num)
{
	for (int i = 0; i < num; i++)
		_space.push_back(new SPACE(i));
	_building = NULL;

	_groundLight = IMAGEMANAGER->addDImage("groundHighlight", L"img/groundhighlight.png", 90, 120);

	//처음 위치기준 좌우 7칸 남는 공간으로
	for (int i = num / 2 - 9; i < num / 2 + 9; i++)
		_space[i]->empty = true;


	//cityHall
	addBuilding(num / 2 - 2, 0);

	_cursor = GAMEMANAGER->getPlayer()->getCursor();

	_possible = false;

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

	if (_building) isPossible();
}

void BuildManager::render()
{
	buildIter building = _buildings.begin();
	for (; building != _buildings.end(); ++building) {
		(*building)->render();
		//COLLISIONMANAGER->buildingsWithCursor(*building, _cursor->getBackX(), _cursor->getBackY());
	}

	if (_building) spaceRender();
}

void BuildManager::isPossible()
{
	spaceIter space = _space.begin();
	bool needColTest = true;
	GAMEMANAGER->getPlayer()->getCard()->setHide(false);

	for (; space != _space.end(); ++space) {
		if (!(*space)->empty) continue;
		if (!needColTest) continue;

		_possible = false;
		if (COLLISIONMANAGER->spaceWithCursor((*space)->body, _cursor->getBackX(), _cursor->getBackY())) {
			needColTest = false;
			GAMEMANAGER->getPlayer()->getCard()->setHide(true);

			int spaceCost = _building->getSpace();
			_possible = true;
			_building->init((*space)->idX);

			for (int i = 1; i < spaceCost; ++i) {
				if ((*(space + i))->empty) continue;

				_possible = false;
				break;
			}
		}
	}
}

void BuildManager::spaceRender()
{
	spaceIter space = _space.begin();

	if(_possible) _building->preview();

	for (; space != _space.end(); ++space) {
		if (!(*space)->empty) continue;

		_groundLight->render((*space)->idX * 90, GROUND - _groundLight->getHeight());

		if (PRINTMANAGER->isDebug()) {
			WCHAR tmp[128];

			swprintf_s(tmp, L"idX : %d", (*space)->idX);
			DTDMANAGER->printText(tmp, (*space)->body.left + 50, (*space)->body.top - 30, 100, 50);

			DTDMANAGER->Rectangle((*space)->body);
		}
	}

}

void BuildManager::grabBcard()
{
	Card* card = GAMEMANAGER->getPlayer()->getCard();

	if (!_building) {
		_building = DICTIONARY->makeBuilding(card->getCardStat()->number, card->getCardStat()->level);
		_building->init(card->getReward());
	}
}

void BuildManager::putBcard()
{
	SAFE_DELETE(_building);
}

void BuildManager::addBuilding()
{
	if (!_possible) return;

	//공간 사용
	int space = _building->getSpace();
	int idX = _building->getIdX();
	for (int i = idX; i < idX + space; i++)
		_space[i]->empty = false;

	GAMEMANAGER->getPlayer()->getCard()->setHide(false);
	_buildings.push_back(_building);

	GAMEMANAGER->getPlayer()->changeGold(_building->getReward()[REWARD_TYPE_GOLD]);
	GAMEMANAGER->getPlayer()->changePrize(_building->getReward()[REWARD_TYPE_PRIZE]);
	GAMEMANAGER->getPlayer()->changeTax(_building->getReward()[REWARD_TYPE_TAX]);
	GAMEMANAGER->getPlayer()->changeMaxCivil(_building->getReward()[REWARD_TYPE_CIVIL]);

	_building = NULL;
}

Building * BuildManager::addBuilding(int idX, int num, int level)
{
	Building* building = DICTIONARY->makeBuilding(num, level);

	//제대로 못불러왔으면 NULL
	if (!building) return building;

	building->init(idX);
	int space = building->getSpace();
	for (int i = idX; i < idX + space; i++)
		_space[i]->empty = false;

	_buildings.push_back(building);

	return building;
}

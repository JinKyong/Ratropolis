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

	_groundLight = IMAGEMANAGER->addDImage("groundHighlight", L"img/build/effect/groundhighlight.png", 90, 120);
	_wall = IMAGEMANAGER->addDImage("wallReady", L"img/build/effect/WallReady.png", 268, 156);
	_wallLight = IMAGEMANAGER->addDImage("wallReadyHighlight", L"img/build/effect/WallReady_Highlight.png", 268, 156);

	//ó�� ��ġ���� �¿� 7ĭ ���� ��������
	for (int i = num / 2 - 9; i < num / 2 + 9; i++)
		_space[i]->empty = true;

	//cityHall
	addBuilding(num / 2 - 2, 0);
	addBuilding(num / 2 - 11, 18, 1);
	addBuilding(num / 2 + 9, 18, 1, true);

	//��
	_leftWall = num / 2 - 20;
	_rightWall = num / 2 + 18;

	//�÷��̾� ����
	Player* player = GAMEMANAGER->getPlayer();
	player->changeMaxLeft(_leftWall);
	player->changeMaxRight(_rightWall);
	_cursor = player->getCursor();

	_getWall = 0;
	_possible = false;

	return S_OK;
}

void BuildManager::release()
{
	buildIter build = _buildings.begin();
	for (; build != _buildings.end();) {
		SAFE_RELEASE(*build);
		build = _buildings.erase(build);
	}

	_buildings.clear();
}

void BuildManager::update()
{
	buildIter building = _buildings.begin();
	for (; building != _buildings.end();) {
		(*building)->update();
		++building;
	}

	if (_getWall) isPossibleWall();
	else if (_building) isPossible();
}

void BuildManager::render()
{
	//�� && �� ���� highlight
	if (_getWall) wallRender();
	else if (_building) spaceRender();

	//�� ���
	for (int i = _leftWall; i > 0; i -= 9) {
		if (i == _getWall) continue;
		_wall->render(i * 90, GROUND - _wall->getHeight());
	}
	for (int i = _rightWall; i < _space.size(); i += 9) {
		if (i == _getWall) continue;
		_wall->render(i * 90, GROUND - _wall->getHeight());
	}

	//�ǹ� ���
	buildIter building = _buildings.begin();
	for (; building != _buildings.end(); ++building) {
		(*building)->render();
		//COLLISIONMANAGER->buildingsWithCursor(*building, _cursor->getBackX(), _cursor->getBackY());
	}
}

void BuildManager::isPossibleWall()
{
	GAMEMANAGER->getPlayer()->getCard()->setHide(false);
	_possible = false;

	if (_leftWall > 8 &&
		( COLLISIONMANAGER->spaceWithCursor(_space[_leftWall]->body, _cursor->getBackX(), _cursor->getBackY()) ||
		COLLISIONMANAGER->spaceWithCursor(_space[_leftWall+1]->body, _cursor->getBackX(), _cursor->getBackY()) ) ) {

		GAMEMANAGER->getPlayer()->getCard()->setHide(true);
		_building->setIdX(_space[_leftWall]->idX);
		_building->setReverse(false);
		_getWall = _leftWall;
		_possible = true;
	}
	else if (_rightWall < _space.size() - 8 &&
		(COLLISIONMANAGER->spaceWithCursor(_space[_rightWall]->body, _cursor->getBackX(), _cursor->getBackY()) ||
			COLLISIONMANAGER->spaceWithCursor(_space[_rightWall + 1]->body, _cursor->getBackX(), _cursor->getBackY()) ) ) {

		GAMEMANAGER->getPlayer()->getCard()->setHide(true);
		_building->setIdX(_space[_rightWall]->idX);
		_building->setReverse(true);
		_getWall = _rightWall;
		_possible = true;
	}
	else
		_getWall = 1;
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
			_building->setIdX((*space)->idX);

			for (int i = 1; i < spaceCost; ++i) {
				if ((*(space + i))->empty) continue;

				_possible = false;
				break;
			}
		}
	}
}

void BuildManager::wallRender()
{
	if (_leftWall != _getWall)
		_wallLight->render(_leftWall * 90, GROUND - _wallLight->getHeight());
	if (_rightWall != _getWall)
		_wallLight->render(_rightWall * 90, GROUND - _wallLight->getHeight());

	if (_possible) _building->preview();
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
		//_building->init(0);

		if (card->getCardStat()->number == 18)
			_getWall = 1;
	}
}

void BuildManager::putBcard()
{
	GAMEMANAGER->getPlayer()->getCard()->setHide(false);
	_getWall = 0;
	SAFE_DELETE(_building);
}

void BuildManager::expandSpace(int idX)
{
	if( !((idX - _leftWall) == 9 ||
		(_rightWall - idX) == 9) ) return;

	//true�� left, false�� right
	bool direct = (idX - _leftWall) == 9 ? true : false;

	if (direct) {
		for (int i = 1; i < 8; i++)
			_space[idX + i + 1]->empty = true;
		GAMEMANAGER->getPlayer()->changeMaxLeft(_leftWall);
	}
	else {
		for (int i = 1; i < 8; i++)
			_space[idX - i]->empty = true;
		GAMEMANAGER->getPlayer()->changeMaxRight(_rightWall);
	}
}

void BuildManager::addWall()
{
	if (!_possible) return;

	Card* card = GAMEMANAGER->getPlayer()->getCard();
	card->setHide(false);

	//�� ����
	int idX = _building->getIdX();
	if (idX == _leftWall) {
		_leftWall -= 9;
		_building->init(idX);
	}
	else if (idX == _rightWall) {
		_rightWall += 9;
		_building->init(idX, true);
	}

	//�ǹ� �߰�
	_building->setReward(card->getReward());
	_building->setOnBuild(true);
	SOUNDMANAGER->play("startConstruct");
	_buildings.push_back(_building);

	_getWall = 0;
	_building = NULL;
}

void BuildManager::addBuilding()
{
	if (!_possible) return;

	//���� ���
	int space = _building->getSpace();
	int idX = _building->getIdX();
	for (int i = idX; i < idX + space; i++)
		_space[i]->empty = false;

	Card* card = GAMEMANAGER->getPlayer()->getCard();
	card->setHide(false);

	//�ǹ� �߰�
	_building->init(idX);
	_building->setReward(card->getReward());
	_building->setOnBuild(true);
	SOUNDMANAGER->play("startConstruct");
	_buildings.push_back(_building);

	_building = NULL;
}

Building * BuildManager::addBuilding(int idX, int num, int level, bool reverse)
{
	Building* building = DICTIONARY->makeBuilding(num, level);

	//����� ���ҷ������� NULL
	if (!building) return building;

	building->init(idX, reverse);
	int space = building->getSpace();
	for (int i = idX; i < idX + space; i++)
		_space[i]->empty = false;

	_buildings.push_back(building);

	return building;
}
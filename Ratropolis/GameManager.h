#pragma once
#include "singletonBase.h"
#include "Building.h"
#include <vector>

class Player;

class GameManager : public singletonBase<GameManager>
{
private:
	typedef vector<Building*>				buildList;
	typedef vector<Building*>::iterator		buildIter;

private:
	RECT _useBox;

	Player* _player;

	buildList	_buildings;
	buildIter	_building;

	//enemyManager
	//npcManager

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void playGame();

	void renderPlayer();





	RECT getUseBox() { return _useBox; }

	Player* getPlayer() { return _player; }

};


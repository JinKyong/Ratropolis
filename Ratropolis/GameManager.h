#pragma once
#include "singletonBase.h"

class Player;

class GameManager : public singletonBase<GameManager>
{
private:
	Player* _player;
	RECT _useBox;

	//buildManager
	//enemyManager
	//npcManager

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void playGame();





	Player* getPlayer() { return _player; }

	RECT getUseBox() { return _useBox; }
};


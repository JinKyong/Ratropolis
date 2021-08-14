#pragma once
#include "singletonBase.h"
#include "BuildManager.h"
#include <vector>

class Player;

class GameManager : public singletonBase<GameManager>
{
private:
	RECT _useBox;

	Player* _player;
	BuildManager* _buildManager;
	//enemyManager;
	//npcManager;

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void playGame();

	void renderPlayer();





	RECT getUseBox() { return _useBox; }

	Player* getPlayer() { return _player; }
	BuildManager* getBuildManager() { return _buildManager; }
};


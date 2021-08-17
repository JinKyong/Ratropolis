#pragma once
#include "singletonBase.h"
#include "BuildManager.h"
#include "NPCManager.h"
#include <vector>

class Player;

class GameManager : public singletonBase<GameManager>
{
private:
	dImage* _fadeImage;

	RECT _useBox;

	Player* _player;
	BuildManager* _buildManager;
	//enemyManager;
	NPCManager* _NPCManager;

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void playGame();
	void renderSight();
	void renderPlayer();





	RECT getUseBox() { return _useBox; }

	Player* getPlayer() { return _player; }
	BuildManager* getBuildManager() { return _buildManager; }
};


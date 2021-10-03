#pragma once
#include "singletonBase.h"
#include "BuildManager.h"
#include "EnemyManager.h"
#include "NPCManager.h"
#include "Button.h"
#include <vector>

class Player;

class GameManager : public singletonBase<GameManager>
{
private:
	dImage* _fadeImage;

	RECT _useBox;
	Player* _player;

	//Shop & Event Button
	BUTTON _shopButton;
	BUTTON _eventButton;
	dImage* _shopButtonHL;
	dImage* _eventButtonHL;

	float _shopCount;
	float _eventCount;
	bool _onShop;
	bool _onEvent;


	//Object
	BuildManager* _buildManager;
	EnemyManager* _enemyManager;
	NPCManager* _NPCManager;


	//Timer
	float _gameTime;				//게임 전체 경과시간
	float _waveTime;				//웨이브 시작 후 경과시간
	bool _firstWaveStart;			//첫 웨이브 시작 여부
	bool _onWave;					//웨이브 진행중인지

	GameManager() {};
	friend singletonBase<GameManager>;

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void playGame();
	void renderSight();
	void renderPlayer();

	void onShop();
	void offShop();
	void onEvent();
	void offEvent();





	RECT getUseBox() { return _useBox; }

	Player* getPlayer() { return _player; }

	PBUTTON getShopButton() { return &_shopButton; }
	PBUTTON getEventButton() { return &_eventButton; }

	BuildManager* getBuildManager() { return _buildManager; }
	EnemyManager* getEnemyManager() { return _enemyManager; }
	NPCManager* getNPCManager() { return _NPCManager; }

	bool getOnWave() { return _onWave; }
	void setOnWave(bool onWave) { _onWave = onWave; }
};


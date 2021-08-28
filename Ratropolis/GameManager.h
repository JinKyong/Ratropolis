#pragma once
#include "singletonBase.h"
#include "BuildManager.h"
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


	void onShop();
	void offShop();
	void onEvent();
	void offEvent();





	RECT getUseBox() { return _useBox; }

	Player* getPlayer() { return _player; }

	PBUTTON getShopButton() { return &_shopButton; }
	PBUTTON getEventButton() { return &_eventButton; }

	BuildManager* getBuildManager() { return _buildManager; }
};


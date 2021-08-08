#pragma once
#include "gameNode.h"
#include "Player.h"

class playGround : public gameNode
{
private:
	Player* _player;

	bool _debug;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
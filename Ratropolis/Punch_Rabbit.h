#pragma once
#include "Enemy.h"

class Punch_Rabbit : public Enemy
{
public:
	Punch_Rabbit();
	~Punch_Rabbit();

	virtual HRESULT init(float x, int direct);
	virtual void release();
	virtual void update();
	virtual void render();
};


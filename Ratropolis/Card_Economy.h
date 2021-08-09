#pragma once
#include "Card.h"

class Card_Economy : public Card
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(float x, float y);

	virtual void useCard();
};


#pragma once
#include "Card.h"

class Icon;

class Card_Economy : public Card
{
protected:
	Icon* _civilCost;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void useCard();
};


#pragma once
#include "Card.h"

class Card_Millitary : public Card
{
protected:
	Icon* _civilCost;
	Icon* _attack;
	Icon* _defense;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void useCard();
};


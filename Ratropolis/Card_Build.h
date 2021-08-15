#pragma once
#include "Card.h"

class Card_Build : public Card
{
protected:
	Icon* _spaceCost;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void useCard();
};


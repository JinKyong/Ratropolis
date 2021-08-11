#pragma once
#include "Menu.h"
#include <vector>

class Card;

class CardBagMenu : public Menu
{
private:
	dImage* _back;

	vector<Card*> _cards;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};


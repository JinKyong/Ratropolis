#pragma once
#include "Menu.h"
#include <vector>

class Card;

class CardGraveMenu : public Menu
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
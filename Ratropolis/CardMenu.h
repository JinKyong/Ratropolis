#pragma once
#include "Menu.h"
#include <vector>
#include <algorithm>

class CardMenu : public Menu
{
private:
	int _type;

	Card* _card;
	vector<Card*> _cards;

public:
	CardMenu(int type = 0);
	~CardMenu();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScroll(float num);

	inline static bool compare(Card* a, Card* b) {
		return a->getCardStat()->number < b->getCardStat()->number;
	}
};


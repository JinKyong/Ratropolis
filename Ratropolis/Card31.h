#pragma once
#include "Card_Economy.h"

class Card31 : public Card_Economy
{
private:
	int _sum;

public:
	Card31(int level);
	~Card31();

	void update();
	void useCard();
};


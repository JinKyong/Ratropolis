#pragma once
#include "Card_Economy.h"

class Card1 : public Card_Economy
{
private:

public:
	Card1(int level);
	~Card1();

	void update();
	void useCard();
};


#pragma once
#include "Card_Economy.h"

class Card32 : public Card_Economy
{
private:
	int _sum;

public:
	Card32();
	~Card32();

	void update();
	void useCard();
};


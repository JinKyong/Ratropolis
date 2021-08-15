#pragma once
#include "Card_Build.h"

class Card3 : public Card_Build
{
public:
	Card3(int level);
	~Card3();

	void update();
	void useCard();
};


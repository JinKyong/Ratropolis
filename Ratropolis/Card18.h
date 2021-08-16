#pragma once
#include "Card_Build.h"

class Card18 : public Card_Build
{
public:
	Card18(int level);
	~Card18();

	void update();
	void useCard();
};


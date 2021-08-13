#pragma once
#include "singletonBase.h"
#include "Card.h"
#include "CardHeader.h"
#include <map>

class CardDict : public singletonBase<CardDict>
{
private:
	typedef Card*(CardDict::*func)(int level);
	typedef map<int, func>		cardList;

private:
	cardList _cardList;

public:
	HRESULT init();
	void release();

	void addCard(int num, func f);
	Card* makeCard(int num, int level = 1) { return (this->*_cardList[num])(level); }



	void setCardImage();
	void registerCardFrameImage();			//카드 frameImg	(틀)
	void registerCardGemImage();			//카드 gemImg	(보석)
	void registerCardIlluste();				//카드 illust	(그림)
	void registerCardCostImage();			//카드 cost		(비용)

	//======================== 카드 도감 ========================//
	Card* card1(int level) { return new Card1(level); }
	Card* card31(int level) { return new Card31(level); }
	Card* card32(int level) { return new Card32(level); }
};


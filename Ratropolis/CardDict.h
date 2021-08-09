#pragma once
#include "singletonBase.h"
#include "Card.h"
#include "CardHeader.h"
#include <map>

class CardDict : public singletonBase<CardDict>
{
private:
	typedef Card*(CardDict::*func)();
	typedef map<int, func>		cardList;

private:
	int _index;
	cardList _cardList;

public:
	HRESULT init();
	void release();

	void addCard(func f);
	Card* makeCard(int num) { return (this->*_cardList[num])(); }



	void setCardImage();
	void registerCardFrameImage();			//카드 frameImg	(틀)
	void registerCardGemImage();			//카드 gemImg	(보석)
	void registerCardIlluste();				//카드 illust	(그림)
	void registerCardCostImage();			//카드 cost		(비용)

	//======================== 카드 도감 ========================//
	//Card* card32() { return new Card32; }
};


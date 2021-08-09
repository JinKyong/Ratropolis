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
	void registerCardFrameImage();			//ī�� frameImg	(Ʋ)
	void registerCardGemImage();			//ī�� gemImg	(����)
	void registerCardIlluste();				//ī�� illust	(�׸�)
	void registerCardCostImage();			//ī�� cost		(���)

	//======================== ī�� ���� ========================//
	//Card* card32() { return new Card32; }
};


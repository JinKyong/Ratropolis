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
	void registerCardFrameImage();			//ī�� frameImg	(Ʋ)
	void registerCardGemImage();			//ī�� gemImg	(����)
	void registerCardIlluste();				//ī�� illust	(�׸�)
	void registerCardCostImage();			//ī�� cost		(���)

	//======================== ī�� ���� ========================//
	Card* card1(int level) { return new Card1(level); }
	Card* card31(int level) { return new Card31(level); }
	Card* card32(int level) { return new Card32(level); }
};


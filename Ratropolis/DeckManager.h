#pragma once
#include "singletonBase.h"
#include "Card.h"
#include <vector>

#define SHUFFLE		1000

class DeckManager : public singletonBase<DeckManager>
{
private:
	typedef	vector<Card*>				deckList;
	typedef	vector<Card*>::iterator		deckIter;

private:
	deckList	_currentDeck;		//현재 덱(현재 모든 카드 리스트)
	deckList	_currentCards;		//현재 카드(현재 손에 가지고 있는 카드)

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void shuffle();

	void registerCardFrameImage();			//카드 frameImg	(틀)
	void registerCardGemImage();			//카드 gemImg	(보석)
	void registerCardIlluste();				//카드 illust	(그림)
	void registerCardCostImage();			//카드 cost		(비용)
};


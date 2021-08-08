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
	deckList	_currentDeck;		//���� ��(���� ��� ī�� ����Ʈ)
	deckList	_currentCards;		//���� ī��(���� �տ� ������ �ִ� ī��)

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void shuffle();

	void registerCardFrameImage();			//ī�� frameImg	(Ʋ)
	void registerCardGemImage();			//ī�� gemImg	(����)
	void registerCardIlluste();				//ī�� illust	(�׸�)
	void registerCardCostImage();			//ī�� cost		(���)
};


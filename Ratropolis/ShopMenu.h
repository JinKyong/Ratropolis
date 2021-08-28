#pragma once
#include "Menu.h"
#include <vector>

class Card;

class ShopMenu : public Menu
{
private:
	typedef vector<Card*>				salesList;
	typedef vector<Card*>::iterator		salesIter;

private:
	//카드 리스트
	salesList	_cardList;
	int			_cardCost[8];
	int			_num;				//남은 카드 수
	int			_selectedCard;		//선택된 카드 인덱스


	//이미지
	dImage* _shopFrame;
	dImage* _goldIcon;
	dImage* _soldOut;


	//버튼(re-roll)
	BUTTON _exit;
	BUTTON _reroll;
	dImage* _buttonHL;
	bool _rollable;


	//선택 카드 & 소지금
	Card* _card;
	int _gold;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScroll(float num);

	void makeCard();
};


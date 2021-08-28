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
	//ī�� ����Ʈ
	salesList	_cardList;
	int			_cardCost[8];
	int			_num;				//���� ī�� ��
	int			_selectedCard;		//���õ� ī�� �ε���


	//�̹���
	dImage* _shopFrame;
	dImage* _goldIcon;
	dImage* _soldOut;


	//��ư(re-roll)
	BUTTON _exit;
	BUTTON _reroll;
	dImage* _buttonHL;
	bool _rollable;


	//���� ī�� & ������
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


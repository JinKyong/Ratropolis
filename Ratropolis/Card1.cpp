#include "stdafx.h"
#include "Card1.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"
#include "Labor.h"

Card1::Card1(int level)
{
	//ī�� ����
	_cardStat.number = 1;					//��ȣ
	_cardStat.level = level;				//����(�ִ� 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//���

	_reward[REWARD_TYPE_GOLD] = 60 + (_cardStat.level - 1) * 30;
	//����
	swprintf_s(_cardStat.desc, L"50�� �� +%d��ȭ", _reward[REWARD_TYPE_GOLD]);

	//�̸�
	_name = new NameTag;
	_name->init(L"�", _cardStat.level);

	//���
	_cost = new Icon_Gold;
	_cost->init(5 + (_cardStat.level - 1) * 3);
	_civilCost = new Icon_Civil;	
	_civilCost->init(2);

	//�Ӽ�(ī�� Ű����)
	_atbList.push_back(new Labor);
	for (int i = 0; i < _atbList.size(); ++i)
		_atbList[i]->init();
}

Card1::~Card1()
{
}

void Card1::update()
{
	Card_Economy::update();


}

void Card1::useCard()
{
	if (!_usable) return;

	//Labor
	UIMANAGER->addCircleBar(_civilCost->getValue(), 50, _reward);

	//cost
	Card_Economy::useCard();
}

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

	_reward = 60 + (_cardStat.level - 1) * 30;
	//����
	swprintf_s(_cardStat.desc, L"50�� �� +%d��ȭ", _reward);	

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
	_atbList[0]->init(_reward, 50);
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

	//ui�Ŵ��� �ҷ��� loading �߰�

	//cost
	Card_Economy::useCard();
}

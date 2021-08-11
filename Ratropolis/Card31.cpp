#include "stdafx.h"
#include "Card31.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"

Card31::Card31()
{
	//ī�� ����
	_cardStat.number = 31;					//��ȣ
	_cardStat.level = 1;					//����(�ִ� 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//���
	_cardStat.desc = L"����ִ� ī�帶�� +10 ��ȭ";		//����

	_name = new NameTag;
	_name->init(L"����");		//�̸�

	_cost = new Icon_Gold;
	_cost->init(17);
	_civilCost = NULL;			//���

	//�Ӽ�(ī�� Ű����)
	//_atbList;
}

Card31::~Card31()
{
}

void Card31::update()
{
	Card_Economy::update();
	
	_sum = DECKMANAGER->getCurrentHands().size() * 10;

}

void Card31::useCard()
{
	if (!_usable) return;

	_player->changeGold(_sum);

	//cost
	Card_Economy::useCard();
}
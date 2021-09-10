#include "stdafx.h"
#include "Card31.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"

Card31::Card31(int level)
{
	//ī�� ����
	_cardStat.number = 31;					//��ȣ
	_cardStat.level = level;				//����(�ִ� 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//���

	_reward[REWARD_TYPE_GOLD] = 10 + (_cardStat.level - 1) * 5;
	//����
	swprintf_s(_cardStat.desc, L"����ִ� ī�帶�� +%d ��ȭ", _reward[REWARD_TYPE_GOLD]);

	//�̸�
	_name = new NameTag;
	_name->init(L"����", _cardStat.level);

	//���
	_cost = new Icon_Gold;
	_cost->init(17 + (_cardStat.level - 1) * 9);
	_civilCost = NULL;
}

Card31::~Card31()
{
}

void Card31::update()
{
	Card_Economy::update();
	
	_sum = DECKMANAGER->getCurrentHands().size() * _reward[REWARD_TYPE_GOLD];
}

void Card31::useCard()
{
	if (!_usable) return;

	_player->changeGold(_sum);

	//cost
	Card_Economy::useCard();
	SOUNDMANAGER->play("useCard31");
}
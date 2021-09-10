#include "stdafx.h"
#include "Card32.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"

Card32::Card32(int level)
{
	//ī�� ����
	_cardStat.number = 32;					//��ȣ
	_cardStat.level = level;				//����(�ִ� 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//���

	_reward[REWARD_TYPE_GOLD] = 30 + (_cardStat.level - 1) * 15;
	//����
	swprintf_s(_cardStat.desc, L"����ִ� ġ��� +%d ��ȭ", _reward[REWARD_TYPE_GOLD]);

	//�̸�
	_name = new NameTag;
	_name->init(L"ġ��", _cardStat.level);

	//���
	_cost = new Icon_Gold;
	_cost->init(40 + (_cardStat.level - 1) * 20);
	_civilCost = NULL;			
}

Card32::~Card32()
{
}

void Card32::update()
{
	Card_Economy::update();

	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	_sum = 0;
	for (int i = 0; i < hands.size(); i++)
		if (hands[i]->getCardStat()->number == _cardStat.number)
			_sum += _reward[REWARD_TYPE_GOLD];

	//WCHAR tmp[128];
	//tmp
}

void Card32::useCard()
{
	if (!_usable) return;

	_player->changeGold(_sum);

	//cost
	Card_Economy::useCard();
	SOUNDMANAGER->play("useCard32");
}

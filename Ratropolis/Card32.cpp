#include "stdafx.h"
#include "Card32.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"

Card32::Card32()
{
	//ī�� ����
	_cardStat.number = 32;					//��ȣ
	_cardStat.level = 1;					//����(�ִ� 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//���
	_cardStat.desc = L"����ִ� ġ��� +30 ��ȭ";		//����

	_name = new NameTag;
	_name->init(L"ġ��");		//�̸�

	_cost = new Icon_Gold;
	_cost->init(40);
	_civilCost = NULL;			//���

	//�Ӽ�(ī�� Ű����)
	//_atbList;
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
			_sum += 30;

	//WCHAR tmp[128];
	//tmp
}

void Card32::useCard()
{
	if (!_usable) return;

	_player->changeGold(_sum);

	//cost
	Card_Economy::useCard();
}

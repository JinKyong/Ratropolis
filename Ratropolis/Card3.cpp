#include "stdafx.h"
#include "Card3.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Space.h"

Card3::Card3(int level)
{
	//ī�� ����
	_cardStat.number = 3;					//��ȣ
	_cardStat.level = level;				//����(�ִ� 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//���

	_reward[REWARD_TYPE_CIVIL] = 3 + (_cardStat.level - 1) * 2;
	_reward[REWARD_TYPE_TAX] = _cardStat.level;
	//����
	swprintf_s(_cardStat.desc, L"%d �ù�, +%d ����", _reward[REWARD_TYPE_CIVIL], _reward[REWARD_TYPE_TAX]);

	//�̸�
	_name = new NameTag;
	_name->init(L"��", _cardStat.level);

	//���
	_cost = new Icon_Gold;
	_cost->init(50 + (_cardStat.level - 1) * 25);
	_spaceCost = new Icon_Space;
	_spaceCost->init(1);

	//�Ӽ�(ī�� Ű����)
	//_atbList.push_back(new Labor);
	//for (int i = 0; i < _atbList.size(); ++i)
	//	_atbList[i]->init();
}

Card3::~Card3()
{
}

void Card3::update()
{
	Card_Build::update();
}

void Card3::useCard()
{
	if (!_usable) {
		GAMEMANAGER->getBuildManager()->putBcard();
		return;
	}

	//�ǹ�����
	GAMEMANAGER->getBuildManager()->addBuilding();

	//cost
	Card_Build::useCard();
}

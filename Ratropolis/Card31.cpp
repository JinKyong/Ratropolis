#include "stdafx.h"
#include "Card31.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"

Card31::Card31(int level)
{
	//카드 내용
	_cardStat.number = 31;					//번호
	_cardStat.level = level;				//레벨(최대 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//등급

	_reward[REWARD_TYPE_GOLD] = 10 + (_cardStat.level - 1) * 5;
	//설명
	swprintf_s(_cardStat.desc, L"들고있는 카드마다 +%d 금화", _reward[REWARD_TYPE_GOLD]);

	//이름
	_name = new NameTag;
	_name->init(L"도공", _cardStat.level);

	//비용
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
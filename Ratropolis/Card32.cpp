#include "stdafx.h"
#include "Card32.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"

Card32::Card32(int level)
{
	//카드 내용
	_cardStat.number = 32;					//번호
	_cardStat.level = level;				//레벨(최대 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//등급

	_reward[REWARD_TYPE_GOLD] = 30 + (_cardStat.level - 1) * 15;
	//설명
	swprintf_s(_cardStat.desc, L"들고있는 치즈마다 +%d 금화", _reward[REWARD_TYPE_GOLD]);

	//이름
	_name = new NameTag;
	_name->init(L"치즈", _cardStat.level);

	//비용
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

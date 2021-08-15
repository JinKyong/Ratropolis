#include "stdafx.h"
#include "Card3.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Space.h"

Card3::Card3(int level)
{
	//카드 내용
	_cardStat.number = 3;					//번호
	_cardStat.level = level;				//레벨(최대 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//등급

	_reward[REWARD_TYPE_CIVIL] = 3 + (_cardStat.level - 1) * 2;
	_reward[REWARD_TYPE_TAX] = _cardStat.level;
	//설명
	swprintf_s(_cardStat.desc, L"%d 시민, +%d 세금", _reward[REWARD_TYPE_CIVIL], _reward[REWARD_TYPE_TAX]);

	//이름
	_name = new NameTag;
	_name->init(L"집", _cardStat.level);

	//비용
	_cost = new Icon_Gold;
	_cost->init(50 + (_cardStat.level - 1) * 25);
	_spaceCost = new Icon_Space;
	_spaceCost->init(1);

	//속성(카드 키워드)
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

	//건물짓기
	GAMEMANAGER->getBuildManager()->addBuilding();

	//cost
	Card_Build::useCard();
}

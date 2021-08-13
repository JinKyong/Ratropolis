#include "stdafx.h"
#include "Card1.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"
#include "Labor.h"

Card1::Card1(int level)
{
	//카드 내용
	_cardStat.number = 1;					//번호
	_cardStat.level = level;				//레벨(최대 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//등급

	_reward = 60 + (_cardStat.level - 1) * 30;
	//설명
	swprintf_s(_cardStat.desc, L"50초 후 +%d금화", _reward);	

	//이름
	_name = new NameTag;
	_name->init(L"곡물", _cardStat.level);

	//비용
	_cost = new Icon_Gold;
	_cost->init(5 + (_cardStat.level - 1) * 3);
	_civilCost = new Icon_Civil;	
	_civilCost->init(2);

	//속성(카드 키워드)
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

	//ui매니저 불러서 loading 추가

	//cost
	Card_Economy::useCard();
}

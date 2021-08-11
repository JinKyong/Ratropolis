#include "stdafx.h"
#include "Card31.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Civil.h"

Card31::Card31()
{
	//카드 내용
	_cardStat.number = 31;					//번호
	_cardStat.level = 1;					//레벨(최대 2)
	_cardStat.rarity = CARD_GRADE_COMMON;	//등급
	_cardStat.desc = L"들고있는 카드마다 +10 금화";		//설명

	_name = new NameTag;
	_name->init(L"도공");		//이름

	_cost = new Icon_Gold;
	_cost->init(17);
	_civilCost = NULL;			//비용

	//속성(카드 키워드)
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
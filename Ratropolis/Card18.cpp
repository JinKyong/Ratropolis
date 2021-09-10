#include "stdafx.h"
#include "Card18.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Space.h"

Card18::Card18(int level)
{
	//카드 내용
	_cardStat.number = 18;					//번호
	_cardStat.level = level;				//레벨(최대 2)
	_cardStat.rarity = CARD_GRADE_RARE;	//등급

	//설명
	swprintf_s(_cardStat.desc, L"400 생명력을 가진 방벽 건설");

	//이름
	_name = new NameTag;
	_name->init(L"방어선", _cardStat.level);

	//비용
	_cost = new Icon_Gold;
	_cost->init(88 + (_cardStat.level - 1) * 44);
	_spaceCost = new Icon_Space;
	_spaceCost->init(_cardStat.level + 1);

	//속성(카드 키워드)
	//_atbList.push_back(new Labor);
	//for (int i = 0; i < _atbList.size(); ++i)
	//	_atbList[i]->init();
}

Card18::~Card18()
{
}

void Card18::update()
{
	Card_Build::update();
}

void Card18::useCard()
{
	if (!_usable) {
		GAMEMANAGER->getBuildManager()->putBcard();
		return;
	}

	//건물짓기
	GAMEMANAGER->getBuildManager()->addWall();

	//cost
	Card_Build::useCard();
	SOUNDMANAGER->play("useCard");
}

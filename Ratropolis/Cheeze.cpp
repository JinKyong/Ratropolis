#include "stdafx.h"
#include "Cheeze.h"

Cheeze::Cheeze()
{
	//카드 내용
	_cardStat.number = 32;					//번호
	_cardStat.rarity = CARD_GRADE_COMMON;	//등급
	_cardStat.mainCost = 40;				//메인 비용(골드)
	_cardStat.subCost =  2;					//서브 비용(시민 or 건물크기 등등)
	_cardStat.level = 1;					//레벨(최대 2)

	_cardStat.name = L"치즈";				//이름
	_cardStat.desc = L"치즈는 치즈지만 치즈는 치즈가 아니다 알간? 모르간? 오르간?";				//설명


	//속성(카드 키워드)
	//_atbList;
}

Cheeze::~Cheeze()
{
}

HRESULT Cheeze::init()
{
	Card_Economy::init();

	_x = 5000;
	_y = 500;
	_body = RectMakeCenter(_x, _y, 400, 600);

	return S_OK;
}

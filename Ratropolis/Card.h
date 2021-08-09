#pragma once
#include "Attribute.h"
#include <vector>

#define CARDWIDTH	400
#define CARDHEIGHT	600

enum CARD_GRADE {
	CARD_GRADE_COMMON,
	CARD_GRADE_RARE,
	CARD_GRADE_EPIC,
	CARD_GRADE_LEGEND,
	END_CARD_GRADE
};

typedef struct tagCard {
	int number;				//번호
	CARD_GRADE rarity;		//등급
	int mainCost;			//메인 비용(골드)
	int subCost;			//서브 비용(시민 or 건물크기 등등)
	int level;				//레벨(최대 2)

	wstring name;			//이름
	wstring desc;			//설명
}CARD_INFO, *PCARD_INFO;

class Card
{
protected:
	//위치 좌표
	float _x, _y;
	float _angle;
	RECT _body;


	//이미지
	dImage* _frame;			//틀
	dImage* _gem;			//레어도(보석)
	dImage* _illuste;		//이미지(그림)
	dImage* _nameTag;		//이름태그
	dImage* _mainCost;		//메인 비용(골드)
	dImage* _subCost;		//서브 비용


	//카드 내용
	CARD_INFO _cardStat;


	//속성(카드 키워드)
	vector<Attribute*> _atbList;

public:
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void render(float x, float y) = 0;

	virtual void useCard() = 0;




	//======================================== 접근자 ========================================//

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
};
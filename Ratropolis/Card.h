#pragma once
#include "Attribute.h"
#include <vector>

class Player;

//400, 600
#define CARDWIDTH	160
#define CARDHEIGHT	240

enum CARD_TYPE {
	CARD_TYPE_ECONOMY,
	CARD_TYPE_MILLITARY,
	CARD_TYPE_BUILD,
	CARD_TYPE_TECH,
	END_CARD_TYPE
};

enum CARD_GRADE {
	CARD_GRADE_COMMON,
	CARD_GRADE_RARE,
	CARD_GRADE_EPIC,
	CARD_GRADE_LEGEND,
	END_CARD_GRADE
};

typedef struct tagCard {
	int number;				//번호
	CARD_TYPE type;			//카드 타입
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
	Player* _player;

	//위치 좌표
	float _x, _y;
	float _angle;
	RECT _body;

	//상태
	bool _select;
	bool _usable;

	//이펙트 이미지 & 프레임
	dImage* _selectEffect;
	dImage* _usableEffect;
	int _frameX, _frameY;
	float _count;


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
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void useCard() = 0;

	void controlFrame();

	//======================================== 접근자 ========================================//

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	RECT getBody() { return _body; }

	bool isSelect() { return _select; }
	void setSelect(bool select) { _select = select; }

	PCARD_INFO getCardStat() { return &_cardStat; }
};
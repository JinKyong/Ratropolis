#pragma once
#include "ToolTip.h"
#include "rewardType.h"
#include <vector>

class Player;
class NameTag;
class Icon;

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
	int level;				//레벨(최대 2)
	CARD_TYPE type;			//카드 타입
	CARD_GRADE rarity;		//등급

	WCHAR desc[128];			//설명
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
	float _zoom;
	bool _usable;
	bool _select;

	//이펙트 이미지 & 프레임
	dImage* _selectEffect;
	dImage* _usableEffect;
	int _frameX, _frameY;
	float _count;


	//이미지
	dImage* _frame;			//틀
	dImage* _gem;			//레어도(보석)
	dImage* _illuste;		//이미지(그림)

	//컴포넌트
	NameTag* _name;			//이름
	Icon* _cost;			//비용
	int _reward[END_REWARD_TYPE] = { 0, };	//보상


	//카드 내용
	CARD_INFO _cardStat;


	//속성(카드 키워드)
	vector<ToolTip*> _atbList;

	//카드 보일지 말지
	bool _hide;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void renderDetailed();

	virtual void useCard() = 0;

	void controlFrame();

	//======================================== 접근자 ========================================//

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	RECT getBody() { return _body; }

	float getZoom() { return _zoom; }
	void setZoom(float zoom) { _zoom = zoom; }
	bool isUsable() { return _usable; }
	void setUsable(bool usable) { _usable = usable; }
	bool isSelect() { return _select; }
	void setSelect(bool select) { _select = select; }

	int* getReward() { return _reward; }

	PCARD_INFO getCardStat() { return &_cardStat; }

	bool getHide() { return _hide; }
	void setHide(bool hide) { _hide = hide; }
};
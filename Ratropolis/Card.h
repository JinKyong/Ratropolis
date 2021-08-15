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
	int number;				//��ȣ
	int level;				//����(�ִ� 2)
	CARD_TYPE type;			//ī�� Ÿ��
	CARD_GRADE rarity;		//���

	WCHAR desc[128];			//����
}CARD_INFO, *PCARD_INFO;

class Card
{
protected:
	Player* _player;

	//��ġ ��ǥ
	float _x, _y;
	float _angle;
	RECT _body;

	//����
	float _zoom;
	bool _usable;
	bool _select;

	//����Ʈ �̹��� & ������
	dImage* _selectEffect;
	dImage* _usableEffect;
	int _frameX, _frameY;
	float _count;


	//�̹���
	dImage* _frame;			//Ʋ
	dImage* _gem;			//���(����)
	dImage* _illuste;		//�̹���(�׸�)

	//������Ʈ
	NameTag* _name;			//�̸�
	Icon* _cost;			//���
	int _reward[END_REWARD_TYPE] = { 0, };	//����


	//ī�� ����
	CARD_INFO _cardStat;


	//�Ӽ�(ī�� Ű����)
	vector<ToolTip*> _atbList;

	//ī�� ������ ����
	bool _hide;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void renderDetailed();

	virtual void useCard() = 0;

	void controlFrame();

	//======================================== ������ ========================================//

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
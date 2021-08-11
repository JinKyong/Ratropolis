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
	int number;				//��ȣ
	CARD_TYPE type;			//ī�� Ÿ��
	CARD_GRADE rarity;		//���
	int mainCost;			//���� ���(���)
	int subCost;			//���� ���(�ù� or �ǹ�ũ�� ���)
	int level;				//����(�ִ� 2)

	wstring name;			//�̸�
	wstring desc;			//����
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
	bool _select;
	bool _usable;

	//����Ʈ �̹��� & ������
	dImage* _selectEffect;
	dImage* _usableEffect;
	int _frameX, _frameY;
	float _count;


	//�̹���
	dImage* _frame;			//Ʋ
	dImage* _gem;			//���(����)
	dImage* _illuste;		//�̹���(�׸�)
	dImage* _nameTag;		//�̸��±�
	dImage* _mainCost;		//���� ���(���)
	dImage* _subCost;		//���� ���


	//ī�� ����
	CARD_INFO _cardStat;


	//�Ӽ�(ī�� Ű����)
	vector<Attribute*> _atbList;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void useCard() = 0;

	void controlFrame();

	//======================================== ������ ========================================//

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	RECT getBody() { return _body; }

	bool isSelect() { return _select; }
	void setSelect(bool select) { _select = select; }

	PCARD_INFO getCardStat() { return &_cardStat; }
};
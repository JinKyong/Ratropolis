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
	int number;				//��ȣ
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
	//��ġ ��ǥ
	float _x, _y;
	float _angle;
	RECT _body;


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
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void render(float x, float y) = 0;

	virtual void useCard() = 0;




	//======================================== ������ ========================================//

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
};
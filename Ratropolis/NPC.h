#pragma once

typedef struct tagBodyPart {
	float datumPointX, datumPointY;	//������ (�̹��� ���� ����)
	D2D1_RECT_F position;			//�̹������� ��ġ
}BPART, *PBPART;

enum BODY_PART {
	BODY_PART_HEAD,
	BODY_PART_BODY,
	BODY_PART_RARM,
	BODY_PART_LARM,
	BODY_PART_RLEG,
	BODY_PART_LLEG,
	BODY_PART_RFOOT,
	BODY_PART_LFOOT,
	BODY_PART_TAIL,
	END_BODY_PART
};

class NPC
{
protected:
	dImage* _image;							//��ü �̹���
	BPART _bPart[END_BODY_PART];			//�� ��ü ��Ʈ
	D2D1_RECT_F _destBPart[END_BODY_PART];	//�� ��ü ��Ʈ ��·�Ʈ
	int _orderRight[END_BODY_PART];			//�� ��ü ��Ʈ ��������(RIGHT)
	int _orderLeft[END_BODY_PART];			//�� ��ü ��Ʈ ��������(LEFT)


	//position
	float _x, _y;		//��ġ��ǥ(�߽�)
	RECT _body;			//�浹 RECT
	int _direct;		//����

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void updatePosition();
	void updateDirect();

	void moveRight();
	void moveLeft();
};
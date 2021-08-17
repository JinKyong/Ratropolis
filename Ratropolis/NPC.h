#pragma once

typedef struct tagBodyPart {
	float datumPointX, datumPointY;	//기준점 (이미지 돌릴 기준)
	D2D1_RECT_F position;			//이미지에서 위치
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
	dImage* _image;					//본체 이미지
	BPART _bPart[END_BODY_PART];	//각 몸체 파트


	//position
	float _x, _y;		//위치좌표(중심)
	RECT _body;			//충돌 RECT
	int _direct;		//방향

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void moveRight();
	void moveLeft();
};
#pragma once
#include "rewardType.h"

#define EACH_SPACE		90
#define GROUND			1500 - 300

class Building
{
protected:
	//Images
	dImage* _bodyImage;


	//Poistion
	int _idX;			//��ġ ��ǥ
	RECT _body;			//�浹 RECT


	//Stat
	int _space;			//���� ����
	int _hp;			//�Ϲ������� 3 ~ 4
	int _level;
	int* _reward;

	bool _active;		//activeȿ�� �ִ��� ����


	//Icon
	//activeIcon
	//refairIcon

public:
	virtual HRESULT init(int idX);
	virtual HRESULT init(int* reward);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void preview();







	int getIdX() { return _idX; }
	void setIdX(int idX) { _idX = idX; }

	RECT getBody() { return _body; }

	int getSpace() { return _space; }
	void setSpace(int space) { _space = space; }

	int* getReward() { return _reward; }
};


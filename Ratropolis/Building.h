#pragma once

#define EACH_SPACE		90

class Building
{
protected:
	//Images
	dImage* _bodyImage;


	//Poistion
	float _x, _y;		//��ġ ��ǥ
	int _space;			//���� ����
	RECT _body;			//�浹 RECT


	//Stat
	int _hp;			//�Ϲ������� 3 ~ 4
	int _level;

	bool _active;		//activeȿ�� �ִ��� ����


	//Icon
	//activeIcon
	//refairIcon

public:
	virtual HRESULT init(float idX, int level = 1);
	virtual void release();
	virtual void update();
	virtual void render();
};


#pragma once

#define EACH_SPACE		90
#define GROUND			1500 - 300

class Building
{
protected:
	//Images
	dImage* _bodyImage;


	//Poistion
	int _idX;			//��ġ ��ǥ
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
	virtual HRESULT init(int idX);
	virtual void release();
	virtual void update();
	virtual void render();







	RECT getBody() { return _body; }
};


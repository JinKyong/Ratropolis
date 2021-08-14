#pragma once

#define EACH_SPACE		90
#define GROUND			1500 - 300

class Building
{
protected:
	//Images
	dImage* _bodyImage;


	//Poistion
	int _idX;			//위치 좌표
	int _space;			//차지 공간
	RECT _body;			//충돌 RECT


	//Stat
	int _hp;			//일반적으로 3 ~ 4
	int _level;

	bool _active;		//active효과 있는지 여부


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


#pragma once

class Building
{
private:
	dImage* _bodyImage;

	int _hp;
	int _spaceCost;		//���� ���

public:
	HRESULT init();
	void release();
	void update();
	void render();
};


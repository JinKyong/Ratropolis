#pragma once

class Building
{
private:
	dImage* _bodyImage;

	int _hp;
	int _spaceCost;		//공간 비용

public:
	HRESULT init();
	void release();
	void update();
	void render();
};


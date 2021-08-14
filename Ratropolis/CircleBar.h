#pragma once
#include "rewardType.h"

class CircleBar
{
private:
	dImage* _backBar;
	dImage* _frontBar;
	dImage* _image;

	int _cost;			//�ù�
	float _elapsedTime;	//����ð�
	float _duration;	//���ӽð�
	int* _reward;		//����

	bool _fin;

public:
	HRESULT init(int cost, float duration, int* reward);
	void release();
	void update();
	void render(float x, float y);






	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};


#pragma once
#include "rewardType.h"

class CircleBar
{
private:
	dImage* _backBar;
	dImage* _frontBar;
	dImage* _image;

	int _cost;			//시민
	float _elapsedTime;	//경과시간
	float _duration;	//지속시간
	int* _reward;		//보상

	bool _fin;

public:
	HRESULT init(int cost, float duration, int* reward);
	void release();
	void update();
	void render(float x, float y);






	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};


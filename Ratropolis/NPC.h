#pragma once

enum NPC_STATE {
	NPC_STATE_IDLE,
	NPC_STATE_MOVE,
	NPC_STATE_ATTACK,
	NPC_STATE_DEATH,
	END_NPC_STATE
};

class NPC
{
protected:
	int _direct;							//방향
	NPC_STATE _currentState;				//현재 상태
	dImage* _stateImage[END_NPC_STATE];		//상태 이미지


	//position
	float _x, _y;		//위치좌표(중심)
	RECT _body;			//충돌 RECT

public:
	HRESULT init(float x);
	void release();
	void update();
	void render();

	void updatePosition();
	void updateDirect();
};
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
	int _direct;							//����
	NPC_STATE _currentState;				//���� ����
	dImage* _stateImage[END_NPC_STATE];		//���� �̹���


	//position
	float _x, _y;		//��ġ��ǥ(�߽�)
	RECT _body;			//�浹 RECT

public:
	HRESULT init(float x);
	void release();
	void update();
	void render();

	void updatePosition();
	void updateDirect();
};
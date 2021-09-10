#pragma once
#include "rewardType.h"

#define EACH_SPACE		90
#define GROUND			1500 - 300
#define BUILD_COUNT		3

class Building
{
protected:
	//Images
	dImage* _bodyImage;
	dImage* _buildEffect;
	dImage* _buildSign;


	//Poistion
	int _idX;			//��ġ ��ǥ
	RECT _body;			//�浹 RECT


	//Stat
	int _space;			//���� ����
	int _hp;			//�Ϲ������� 3 ~ 4
	int _level;
	int _reward[END_REWARD_TYPE] = { 0, };

	bool _active;		//activeȿ�� �ִ��� ����

	//
	float _count;
	float _imageY;
	bool _onBuild;		//�������� ��
	bool _reverse;		//�¿����

	//Icon
	//activeIcon
	//refairIcon

public:
	virtual HRESULT init(int idX, bool reverse = false);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void preview();

	void destroy();
	void addReward();








	int getIdX() { return _idX; }
	void setIdX(int idX) { _idX = idX; }

	RECT getBody() { return _body; }

	int getSpace() { return _space; }
	void setSpace(int space) { _space = space; }

	int* getReward() { return _reward; }
	void setReward(int* reward) { 
		for (int i = 0; i < END_REWARD_TYPE; i++)
			_reward[i] = reward[i];
	}

	bool getActive() { return _active; }
	void setActive(bool active) { _active = active; }
	bool getOnBuild() { return _onBuild; }
	void setOnBuild(bool onBuild) { _onBuild = onBuild; }
	bool getReverse() { return _reverse; }
	void setReverse(bool reverse) { _reverse = reverse; }
};


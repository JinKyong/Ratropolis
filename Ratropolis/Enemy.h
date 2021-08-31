#pragma once

enum ENEMY_STATE {
	ENEMY_STATE_IDLE,
	ENEMY_STATE_MOVE,
	ENEMY_STATE_ATTACK,
	ENEMY_STATE_DEATH,
	END_ENEMY_STATE
};

class Enemy
{
protected:

	//state
	dImage* _stateImages[END_ENEMY_STATE];
	dImage* _currentImage;

	ENEMY_STATE _state;
	bool _isDead;


	//position
	float _x, _y;
	RECT _body;
	RECT _detect;

	//stat
	int _hp;
	int _damage;
	float _speed;


	//frame
	float _count;
	float _renderCount[END_ENEMY_STATE];
	int _frameX, _direct;		// 0 == RIGHT, 1 == LEFT
	float _opacity;



public:
	virtual HRESULT init(float x, int direct);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMY_STATE state);

	void changeHP(int num);







	bool isDead() { return _isDead; }
	void death() { _isDead = true; }

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	RECT getBody() { return _body; }
	RECT getDetect() { return _detect; }

	float getOpacity() { return _opacity; }
	void setOpacity(float opacity) { _opacity = opacity; }
};


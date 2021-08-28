#pragma once
#include "ControlKey.h"

class Player;

enum CURSOR_TYPE {
	CURSOR_TYPE_DEFAULT,
	CURSOR_TYPE_CLICK,
	CURSOR_TYPE_GRAB,
	CURSOR_TYPE_ATTACK,
	CURSOR_TYPE_MINING,
	END_CURSOR_TYPE
};

class Cursor
{
private:
	Player* _player;

	//image
	dImage* _images[END_CURSOR_TYPE];
	dImage* _currentImage;

	//위치좌표
	float _x, _y;
	RECT _body;

	//상대위치좌표
	float _backX, _backY;
	RECT _backBody;

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	//control
	void controlMouse();
	void controlMouseCardList();
	void controlMouseShop();
	void controlMouseEvent();

	//cursor
	void updatePosition(float x, float y);
	void changeCursor(CURSOR_TYPE type);








	//======================================== 접근자 ========================================//
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	RECT getBody() { return _body; }

	float getBackX() { return _backX; }
	void setBackX(float backX) { _backX = backX; }
	float getBackY() { return _backY; }
	void setBackY(float backY) { _backY = backY; }

	RECT getBackBody() { return _backBody; }
};


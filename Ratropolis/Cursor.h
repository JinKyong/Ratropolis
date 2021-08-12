#pragma once

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

	//��ġ��ǥ
	float _x, _y;
	RECT _body;

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void updatePosition(float x, float y);
	void changeCursor(CURSOR_TYPE type);







	//======================================== ������ ========================================//
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	RECT getBody() { return _body; }
};

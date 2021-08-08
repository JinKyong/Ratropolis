#pragma once

enum CURSOR_TYPE {
	CURSOR_TYPE_DEFAULT,
	CURSOR_TYPE_CLICK,
	CURSOR_TYPE_GRAB,
	CURSOR_TYPE_ATTACK,
	CURSOR_TYPE_MINING,
	END_CURSOR_TYPE
};

class Player
{
private:
	dImage* _cursor[END_CURSOR_TYPE];
	dImage* _currentCursor;

	float _x, _y;
	RECT _body;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};


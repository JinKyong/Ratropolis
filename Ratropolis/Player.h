#pragma once

typedef struct tagDefaultStatus {
	int gold;			//돈
	int prize;			//현상금
	int tax;			//세금
	int currentCivil;	//현재 시민
	int maxCivil;		//전체 시민
	int wave;			//현재 웨이브
	//int poison;			//오염도
}DEFAULT_STAT;

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
	//cursor
	dImage* _cursor[END_CURSOR_TYPE];
	dImage* _currentCursor;

	float _x, _y;
	RECT _body;

	//camera중점
	float _camX, _camY;

	DEFAULT_STAT _defaultStat;		//기본 스탯(돈, 시민 등)
	int _level;						//지도자 레벨

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playGame();

	void changeGold(int num);
	void changeCivil(int num);
	void changeMaxCivil(int num);





	static DWORD CALLBACK threadCollectTax(LPVOID lpParameter);


	//======================================== 접근자 ========================================//
	float getCamX() { return _camX; }
	void setCamX(float camX) { _camX = camX; }
	float getCamY() { return _camY; }
	void setCamY(float camY) { _camY = camY; }

	DEFAULT_STAT getDefaultStat() { return _defaultStat; }
};
#pragma once
#include "Cursor.h"

class Card;

typedef struct tagDefaultStatus {
	int gold;			//돈
	int prize;			//현상금
	int tax;			//세금
	int currentCivil;	//현재 시민
	int maxCivil;		//전체 시민
	int wave;			//현재 웨이브
	//int poison;			//오염도
}DEFAULT_STAT;

class Player
{
private:
	Cursor* _cursor;

	//camera중점
	float _camX, _camY;

	DEFAULT_STAT _defaultStat;		//기본 스탯(돈, 시민 등)
	int _level;						//지도자 레벨
	float _count;					//세금 카운트

	//선택 카드
	Card* _selectedCard;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playGame();
	void controlKeyboard();

	void changeGold(int num);
	void changeCivil(int num);
	void changeMaxCivil(int num);
	void changeCard(Card* card);




	//======================================== 접근자 ========================================//
	Cursor* getCursor() { return _cursor; }

	float getCamX() { return _camX; }
	void setCamX(float camX) { _camX = camX; }
	float getCamY() { return _camY; }
	void setCamY(float camY) { _camY = camY; }

	DEFAULT_STAT getDefaultStat() { return _defaultStat; }

	Card* getCard() { return _selectedCard; }
	void setCard(Card* card) { _selectedCard = card; }
};
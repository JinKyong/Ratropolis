#pragma once
#include "singletonBase.h"
#include "Button.h"
#include <vector>

class Player;
class Card;
class Building;
class WaveBar;

class collisionManager : public singletonBase<collisionManager>
{
private:
	Player* _player;

	collisionManager() {};
	friend singletonBase<collisionManager>;

public:	
	HRESULT init();
	void release();
	
	//커서와 배경(건물) 충돌(backRT)
	void buildingsWithCursor(Building* building, float x, float y);
	bool spaceWithCursor(RECT space, float x, float y);
	void selectedButtonSnE(float x, float y);			//Shop & Evnet 버튼 선택


	//커서와 카드(리스트) 충돌(UIRT)
	Card* cardListWithCursor(Card* card, float x, float y);		//카드(리스트)와 커서 충돌
	Card* selectedCard(vector<Card*> cards, float x, float y);	//카드(리스트)와 커서(선택) 충돌
	void selectedButtonUI(float x, float y);					//UI버튼 선택
	void barWithCursor(float x, float y);			//웨이브 바와 커서 충돌


	//커서와 버튼(이벤트) 충돌(cardRT)
	void selectButtonWithCursor(RECT* button, float x, float y);	//버튼(이벤트)과 커서 충돌


	//커서와 카드(핸드) 충돌(cardRT)
	void handsWithCursor(float x, float y);				//카드(핸드)와 커서 충돌
	bool grabbedCard(float x, float y);					//카드(핸드) 드래그(선택)
	void handsWithUseBox(Card* card, float x, float y);	//카드(핸드) 사용

	void buttonWithCursor(PBUTTON button, float x, float y);	//버튼 충돌
};
#pragma once
#include "singletonBase.h"
#include <vector>

class Player;
class Card;
class Building;

class collisionManager : public singletonBase<collisionManager>
{
private:
	Player* _player;

public:
	collisionManager() {};
	~collisionManager() {};

	HRESULT init();
	void release();
	
	//커서와 배경(건물) 충돌(backRT)
	void buildingsWithCursor(Building* building, float x, float y);


	//커서와 카드(리스트) 충돌(UIRT)
	Card* cardListWithCursor(Card* card, float x, float y);		//카드(리스트)와 커서 충돌
	Card* selectedCard(vector<Card*> cards, float x, float y);	//카드(리스트)와 커서(선택) 충돌


	//커서와 카드(핸드) 충돌(cardRT)
	void handsWithCursor();				//카드(핸드)와 커서 충돌
	bool grabbedCard();					//카드(핸드) 드래그(선택)
	void handsWithUseBox(Card* card);	//카드(핸드) 사용
	void buttonWithCursor();			//버튼 선택
};
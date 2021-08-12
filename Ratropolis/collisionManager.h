#pragma once
#include "singletonBase.h"
#include <vector>

class Player;
class Card;

class collisionManager : public singletonBase<collisionManager>
{
private:
	Player* _player;

public:
	collisionManager() {};
	~collisionManager() {};

	HRESULT init();
	void release();
	

	Card* cardListWithCursor(vector<Card*> cards, float x, float y);	//카드(리스트)와 커서 충돌
	Card* selectedCard(vector<Card*> cards, float x, float y);			//카드(리스트)와 커서(선택) 충돌

	void handsWithCursor();				//카드(핸드)와 커서 충돌

	//커서 조작시 충돌
	bool grabbedCard();					//카드(핸드) 드래그(선택)
	void handsWithUseBox(Card* card);	//카드(핸드) 사용
	void buttonWithCursor();			//버튼 선택
};
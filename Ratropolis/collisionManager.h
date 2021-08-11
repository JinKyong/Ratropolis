#pragma once
#include "singletonBase.h"

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
	

	void handsWithCursor();				//카드와 커서 충돌

	//커서 조작시 충돌
	bool grabbedCard();					//카드 드래그(선택)
	void handsWithUseBox(Card* card);	//카드 사용
	void buttonWithCursor();			//버튼 선택
};
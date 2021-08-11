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
	

	bool grabbedCard();		//카드 드래그(선택)
	void handsWithPlayer();	//카드와 커서 충돌

	void handsWithUseBox(Card* card);	//카드 사용
};
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
	

	bool grabbedCard();		//ī�� �巡��(����)
	void handsWithPlayer();	//ī��� Ŀ�� �浹

	void handsWithUseBox(Card* card);	//ī�� ���
};
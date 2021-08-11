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
	

	void handsWithCursor();				//ī��� Ŀ�� �浹

	//Ŀ�� ���۽� �浹
	bool grabbedCard();					//ī�� �巡��(����)
	void handsWithUseBox(Card* card);	//ī�� ���
	void buttonWithCursor();			//��ư ����
};
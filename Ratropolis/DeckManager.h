#pragma once
#include "singletonBase.h"
#include "Card.h"
#include <vector>

#define SHUFFLE		1000

enum DECK_THREAD_TYPE {
	DECK_THREAD_TYPE_SHUFFLE,
	DECK_THREAD_TYPE_DRAW,
	END_DECK_THREAD_TYPE
};

class DeckManager : public singletonBase<DeckManager>
{
private:
	typedef	vector<Card*>				cardList;
	typedef	vector<Card*>::iterator		cardIter;

private:
	cardList	_currentDeck;		//���� ��(���� ��� ī�� ����Ʈ)
	cardList	_currentHands;		//���� ī��(���� �տ� ������ �ִ� ī��)
	cardList	_cardBag;			//ī�� ����(���� ���� ���� ī��)
	cardList	_cardGrave;			//ī�� ����(����� ī��)
	int _index;

	//�̴� ī�� ��
	int _draw;

	//ī����� ��������
	float _x, _y;
	//float _angle;


	HANDLE _threads[END_DECK_THREAD_TYPE];

public:

	HRESULT init();
	void release();
	void update();
	void render();

	//ī�� �߰��ϱ�
	void addCard2Deck(Card* card);
	void addCard2Hand();
	void addCard2Grave(Card* card);

	//ī�� ����
	void sortHands();

	//ī�� ���� �� ��ο�
	void shuffle();
	void drawCard();

	static DWORD CALLBACK threadShuffle(LPVOID lpParameter);
	void releaseShuffleThread();
	static DWORD CALLBACK threadDrawCard(LPVOID lpParameter);
	void releaseDrawThread();



	//======================================== ������ ========================================//
	cardList getCurrentDeck() { return _currentDeck; }
	cardList getCurrentHands() { return _currentHands; }
	cardList getCardGrave() { return _cardGrave; }
	cardList getCardBag() { return _cardBag; }

	int getIndex() { return _index; }
	void setIndex(int index) { _index = index; }

	int getDraw() { return _draw; }
	void setDraw(int draw) { _draw = draw; }

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	HANDLE* getThreads() { return _threads; }
};


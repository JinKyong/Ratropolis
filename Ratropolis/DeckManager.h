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
	cardList	_currentDeck;		//현재 덱(현재 모든 카드 리스트)
	cardList	_currentHands;		//현재 카드(현재 손에 가지고 있는 카드)
	cardList	_cardBag;			//카드 가방(아직 뽑지 않은 카드)
	cardList	_cardGrave;			//카드 무덤(사용한 카드)
	int _index;

	//뽑는 카드 수
	int _draw;

	//카드출력 시작지점
	float _x, _y;
	//float _angle;


	HANDLE _threads[END_DECK_THREAD_TYPE];

public:

	HRESULT init();
	void release();
	void update();
	void render();

	//카드 추가하기
	void addCard2Deck(Card* card);
	void addCard2Hand();
	void addCard2Grave(Card* card);

	//카드 정렬
	void sortHands();

	//카드 셔플 및 드로우
	void shuffle();
	void drawCard();

	static DWORD CALLBACK threadShuffle(LPVOID lpParameter);
	void releaseShuffleThread();
	static DWORD CALLBACK threadDrawCard(LPVOID lpParameter);
	void releaseDrawThread();



	//======================================== 접근자 ========================================//
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


#include "stdafx.h"
#include "DeckManager.h"
#include "Cheeze.h"

HRESULT DeckManager::init()
{
	//쓰레드 핸들
	_threads[DECK_THREAD_TYPE_SHUFFLE] = NULL;
	_threads[DECK_THREAD_TYPE_DRAW] = NULL;

	_draw = 5;

	for (int i = 0; i < 7; i++) {
		Card* card = new Cheeze;
		card->init();
		addCard2Deck(card);
	}

	shuffle();

	return S_OK;
}

void DeckManager::release()
{
	cardIter card = _currentDeck.begin();

	for (; card != _currentDeck.end();) {
		if ((*card)) {
			SAFE_RELEASE(*card);
			card = _currentDeck.erase(card);
		}
		else
			++card;
	}

	_currentDeck.clear();
	_currentHands.clear();
	_cardBag.clear();
	_cardGrave.clear();
}

void DeckManager::update()
{
	//카드 충돌검사
}

void DeckManager::render()
{
	//if (_currentHands.size() <= 0) return;

	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_UI);

	DTDMANAGER->beginDraw();

	for (int i = 0; i < _currentHands.size(); i++)
		_currentHands[i]->render(_x + i * 100, _y);


	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];
		D2D1_RECT_F tmpRECT = dRectMake(20, 20, 200, 100);

		swprintf_s(tmp, L"cards : %d", _currentDeck.size());
		DTDMANAGER->printText(tmp, tmpRECT, 30);

		tmpRECT = dRectMake(20, 40, 200, 100);
		swprintf_s(tmp, L"index : %d", _index);
		DTDMANAGER->printText(tmp, tmpRECT, 30);
	}

	DTDMANAGER->endDraw();

	DTDMANAGER->changeRenderTargetPast();
}

void DeckManager::addCard2Deck(Card * card)
{
	_currentDeck.push_back(card);
}

void DeckManager::addCard2Hand()
{
	_currentHands.push_back(_currentDeck[_index]);
	_index++;
}

void DeckManager::addCard2Grave(Card * card)
{
	_cardGrave.push_back(card);
}

void DeckManager::sortHands()
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY - 100;

	_x -= (_currentHands.size() - 1) * 50;
}

void DeckManager::shuffle()
{
	//예외처리
	//이미 셔플중이면 셔플 안 함
	if (_threads[DECK_THREAD_TYPE_SHUFFLE]) return;

	//쓰레드를 써보십시다
	_threads[DECK_THREAD_TYPE_SHUFFLE] = CreateThread(
		NULL,			//스레드의 보안속성(자신윈도우가 존재할때)
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드)
		threadShuffle,	//사용할 함수
		this,			//스레드 매개변수(this로 뒀으니 본 클래스)
		NULL,			//스레드 특성(기다릴지 바로실행할지(NULL))
		NULL			//스레드 생성 후 스레드의 ID 넘겨줌
	);
}

void DeckManager::drawCard()
{
	//예외처리
	//이미 드로우중이면 드로우 안 함
	if (_threads[DECK_THREAD_TYPE_DRAW]) return;

	//핸드 비우고
	_currentHands.clear();

	//쓰레드를 써보십시다
	_threads[DECK_THREAD_TYPE_DRAW] = CreateThread(
		NULL,			//스레드의 보안속성(자신윈도우가 존재할때)
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드)
		threadDrawCard,	//사용할 함수
		this,			//스레드 매개변수(this로 뒀으니 본 클래스)
		true,			//스레드 특성(기다릴지 바로실행할지(NULL))
		NULL			//스레드 생성 후 스레드의 ID 넘겨줌
	);
}

DWORD DeckManager::threadShuffle(LPVOID lpParameter)
{
	DeckManager* deckHelper = (DeckManager*)lpParameter;

	int index1, index2;
	Card* tmp;
	cardList deck = deckHelper->getCurrentDeck();

	for (int i = 0; i < 1000; i++) {
		index1 = RND->getInt(deck.size());
		index2 = RND->getInt(deck.size());

		tmp = deck[index1];
		deck[index1] = deck[index2];
		deck[index2] = tmp;
	}

	deckHelper->setIndex(0);
	deckHelper->releaseShuffleThread();

	return 0;
}

void DeckManager::releaseShuffleThread()
{
	_threads[DECK_THREAD_TYPE_SHUFFLE] = NULL;
}

DWORD DeckManager::threadDrawCard(LPVOID lpParameter)
{
	DeckManager* deckHelper = (DeckManager*)lpParameter;

	cardList deck = deckHelper->getCurrentDeck();
	int number = deckHelper->getDraw();

	while (number > 0)
	{
		if (deckHelper->getThreads()[DECK_THREAD_TYPE_SHUFFLE])	continue;

		if (deckHelper->getIndex() == deck.size()) {
			deckHelper->shuffle();
			continue;
		}

		deckHelper->addCard2Hand();
		deckHelper->sortHands();

		Sleep(250);

		number--;
	}

	deckHelper->releaseDrawThread();

	return 0;
}

void DeckManager::releaseDrawThread()
{
	_threads[DECK_THREAD_TYPE_DRAW] = NULL;
}

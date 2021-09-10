#include "stdafx.h"
#include "DeckManager.h"
#include "Player.h"

HRESULT DeckManager::init()
{
	//쓰레드 핸들
	_threads[DECK_THREAD_TYPE_SHUFFLE] = NULL;
	_threads[DECK_THREAD_TYPE_DRAW] = NULL;


	_draw = 5;

	for (int i = 0; i < 2; i++) {
		Card* card = DICTIONARY->makeCard(1, RND->getInt(2) + 1);
		card->init();
		addCard2Deck(card);
	}
	for (int i = 0; i < 1; i++) {
		Card* card = DICTIONARY->makeCard(31, RND->getInt(2) + 1);
		card->init();
		addCard2Deck(card);
	}
	for (int i = 0; i < 5; i++) {
		Card* card = DICTIONARY->makeCard(32, RND->getInt(2) + 1);
		card->init();
		addCard2Deck(card);
	}
	for (int i = 0; i < 4; i++) {
		Card* card = DICTIONARY->makeCard(3, RND->getInt(2) + 1);
		card->init();
		addCard2Deck(card);
	}
	for (int i = 0; i < 2; i++) {
		Card* card = DICTIONARY->makeCard(18, RND->getInt(2) + 1);
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
	cardIter card = _currentHands.begin();
	for (; card != _currentHands.end(); card++)
		(*card)->update();

	//카드 정렬
	sortHands();

	//카드 충돌검사
	if (GAMEMANAGER->getPlayer()->getCard())
		GAMEMANAGER->getPlayer()->getCard()->setSelect(true);
	else
		COLLISIONMANAGER->handsWithCursor(_ptMouse.x, _ptMouse.y);
}

void DeckManager::render()
{
	if (UIMANAGER->getOpen()) return;
	//if (_currentHands.size() <= 0) return;

	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_CARD);

	DTDMANAGER->beginDraw();

	for (int i = 0; i < _currentHands.size(); i++)
		_currentHands[i]->render();


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

void DeckManager::useCard(Card * card)
{
	cardIter hand = _currentHands.begin();
	for (; hand != _currentHands.end(); ++hand) {
		if ((*hand) == card) {
			switch ((*hand)->getCardStat()->type) {
			case CARD_TYPE_BUILD:
				//덱에서 삭제
				eraseCard((*hand));

				//카드 지우고
				SAFE_DELETE((*hand));
				//손에서 삭제
				_currentHands.erase(hand);
				break;

			default:
				addCard2Grave((*hand));
				(*hand)->init();
				_currentHands.erase(hand);
				break;
			}

			SOUNDMANAGER->stop("activeCard");
			break;
		}
	}
}

void DeckManager::addCard2Deck(Card * card)
{
	_currentDeck.push_back(card);
	addCard2Bag(card);
}

void DeckManager::addCard2Hand(Card* card)
{
	_currentHands.push_back(card);
}

void DeckManager::addCard2Bag(Card* card)
{
	_cardBag.push_back(card);
}

void DeckManager::addCard2Grave(Card * card)
{
	_cardGrave.push_back(card);
}

void DeckManager::drawCard(int num)
{
	//뽑을 카드가 없으면 다시 셔플
	if (getCardBag().size() <= 0) {
		shuffle();
		return;
	}

	for (int i = 0; i < num; i++) {
		addCard2Hand(_cardBag[0]);
		_cardBag.erase(_cardBag.begin());
		SOUNDMANAGER->play("drawCard");
	}
}

void DeckManager::eraseCard(Card * card)
{
	cardIter deck = _currentDeck.begin();
	for (; deck != _currentDeck.end(); ++deck) {
		if ((*deck) == card) {
			_currentDeck.erase(deck);
			break;
		}
	}
}

void DeckManager::sortHands()
{
	_span = (float)125 / _currentHands.size() + 75;

	cardIter card = _currentHands.begin();
	for (int i=0; card != _currentHands.end(); card++, i++) {
		(*card)->setX(WINSIZEX / 2 - (_currentHands.size() - 1) * _span / 2 + _span * i);
		(*card)->setY(WINSIZEY - 100);
		(*card)->setSelect(false);
		(*card)->setZoom(1.0);
	}
}

void DeckManager::sortHandsSelect(int index)
{
	if (_currentHands[index]->isSelect()) return;

	_currentHands[index]->setSelect(true);
	_currentHands[index]->setZoom(2.0);
	_currentHands[index]->setY(WINSIZEY - 200);

	for (int i = 0; i < index; i++)
		_currentHands[i]->setX(_currentHands[i]->getX() - CARDWIDTH);

	for (int i = index + 1; i < _currentHands.size(); i++)
		_currentHands[i]->setX(_currentHands[i]->getX() + CARDWIDTH);
}

void DeckManager::shuffle()
{
	//예외처리
	//이미 셔플중이면 셔플 안 함
	if (_threads[DECK_THREAD_TYPE_SHUFFLE]) return;

	//카드 무덤 비우고
	cardIter card = _cardGrave.begin();
	for (; card != _cardGrave.end();) {
		_cardBag.push_back(*card);
		card = _cardGrave.erase(card);
	}

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

void DeckManager::redrawCard()
{
	//예외처리
	//이미 드로우중이면 드로우 안 함
	if (_threads[DECK_THREAD_TYPE_DRAW]) return;

	//핸드 비우고
	cardIter card = _currentHands.begin();
	for (; card != _currentHands.end();) {
		_cardGrave.push_back(*card);
		card = _currentHands.erase(card);
	}

	//쓰레드를 써보십시다
	_threads[DECK_THREAD_TYPE_DRAW] = CreateThread(
		NULL,			//스레드의 보안속성(자신윈도우가 존재할때)
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드)
		threadRedrawCard,	//사용할 함수
		this,			//스레드 매개변수(this로 뒀으니 본 클래스)
		true,			//스레드 특성(기다릴지 바로실행할지(NULL))
		NULL			//스레드 생성 후 스레드의 ID 넘겨줌
	);
}

DWORD DeckManager::threadShuffle(LPVOID lpParameter)
{
	DeckManager* deckHelper = (DeckManager*)lpParameter;
	srand(time(NULL));

	int index1, index2;
	Card* tmp;
	cardList cardBag = deckHelper->getCardBag();

	for (int i = 0; i < 1000; i++) {
		index1 = RND->getInt(cardBag.size());
		index2 = RND->getInt(cardBag.size());

		tmp = cardBag[index1];
		cardBag[index1] = cardBag[index2];
		cardBag[index2] = tmp;
	}

	//deckHelper->setIndex(0);
	deckHelper->setCardBag(cardBag);
	deckHelper->releaseShuffleThread();

	return 0;
}

void DeckManager::releaseShuffleThread()
{
	_threads[DECK_THREAD_TYPE_SHUFFLE] = NULL;
}

DWORD DeckManager::threadRedrawCard(LPVOID lpParameter)
{
	DeckManager* deckHelper = (DeckManager*)lpParameter;

	cardList deck = deckHelper->getCurrentDeck();
	int number = deckHelper->getDraw();

	while (number > 0)
	{
		if (deckHelper->getThreads()[DECK_THREAD_TYPE_SHUFFLE])	continue;
		
		//뽑을 카드가 없으면 다시 셔플
		if (deckHelper->getCardBag().size() <= 0) {
			deckHelper->shuffle();
			continue;
		}

		deckHelper->drawCard();

		Sleep(250);

		number--;
	}

	deckHelper->releaseRedrawThread();

	return 0;
}

void DeckManager::releaseRedrawThread()
{
	_threads[DECK_THREAD_TYPE_DRAW] = NULL;
}

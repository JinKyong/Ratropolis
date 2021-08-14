#include "stdafx.h"
#include "DeckManager.h"
#include "Player.h"

HRESULT DeckManager::init()
{
	//������ �ڵ�
	_threads[DECK_THREAD_TYPE_SHUFFLE] = NULL;
	_threads[DECK_THREAD_TYPE_DRAW] = NULL;


	_draw = 5;

	for (int i = 0; i < 10; i++) {
		Card* card = CARDDICT->makeCard(1, RND->getInt(2) + 1);
		card->init();
		addCard2Deck(card);
	}
	for (int i = 0; i < 10; i++) {
		Card* card = CARDDICT->makeCard(31, RND->getInt(2) + 1);
		card->init();
		addCard2Deck(card);
	}
	for (int i = 0; i < 10; i++) {
		Card* card = CARDDICT->makeCard(32, RND->getInt(2) + 1);
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

	//ī�� ����
	sortHands();

	//ī�� �浹�˻�
	if (GAMEMANAGER->getPlayer()->getCard())
		GAMEMANAGER->getPlayer()->getCard()->setSelect(true);
	else
		COLLISIONMANAGER->handsWithCursor();
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
			addCard2Grave((*hand));
			(*hand)->init();
			_currentHands.erase(hand);
			break;
		}
	}
}

void DeckManager::addCard2Deck(Card * card)
{
	_currentDeck.push_back(card);
	_cardBag.push_back(card);
}

void DeckManager::addCard2Hand()
{
	_currentHands.push_back(_cardBag[0]);
	_cardBag.erase(_cardBag.begin());
}

void DeckManager::addCard2Bag()
{
}

void DeckManager::addCard2Grave(Card * card)
{
	_cardGrave.push_back(card);
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
	//����ó��
	//�̹� �������̸� ���� �� ��
	if (_threads[DECK_THREAD_TYPE_SHUFFLE]) return;

	//ī�� ���� ����
	cardIter card = _cardGrave.begin();
	for (; card != _cardGrave.end();) {
		_cardBag.push_back(*card);
		card = _cardGrave.erase(card);
	}

	//�����带 �Ẹ�ʽô�
	_threads[DECK_THREAD_TYPE_SHUFFLE] = CreateThread(
		NULL,			//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,			//�������� ����ũ��(NULL�� �θ� ���ξ�����)
		threadShuffle,	//����� �Լ�
		this,			//������ �Ű�����(this�� ������ �� Ŭ����)
		NULL,			//������ Ư��(��ٸ��� �ٷν�������(NULL))
		NULL			//������ ���� �� �������� ID �Ѱ���
	);
}

void DeckManager::drawCard()
{
	//����ó��
	//�̹� ��ο����̸� ��ο� �� ��
	if (_threads[DECK_THREAD_TYPE_DRAW]) return;

	//�ڵ� ����
	cardIter card = _currentHands.begin();
	for (; card != _currentHands.end();) {
		_cardGrave.push_back(*card);
		card = _currentHands.erase(card);
	}

	//�����带 �Ẹ�ʽô�
	_threads[DECK_THREAD_TYPE_DRAW] = CreateThread(
		NULL,			//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,			//�������� ����ũ��(NULL�� �θ� ���ξ�����)
		threadDrawCard,	//����� �Լ�
		this,			//������ �Ű�����(this�� ������ �� Ŭ����)
		true,			//������ Ư��(��ٸ��� �ٷν�������(NULL))
		NULL			//������ ���� �� �������� ID �Ѱ���
	);
}

DWORD DeckManager::threadShuffle(LPVOID lpParameter)
{
	DeckManager* deckHelper = (DeckManager*)lpParameter;

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

DWORD DeckManager::threadDrawCard(LPVOID lpParameter)
{
	DeckManager* deckHelper = (DeckManager*)lpParameter;

	cardList deck = deckHelper->getCurrentDeck();
	int number = deckHelper->getDraw();

	while (number > 0)
	{
		if (deckHelper->getThreads()[DECK_THREAD_TYPE_SHUFFLE])	continue;

		if (deckHelper->getCardBag().size() <= 0) {
			deckHelper->shuffle();
			continue;
		}

		deckHelper->addCard2Hand();

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

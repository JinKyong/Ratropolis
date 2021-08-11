#include "stdafx.h"
#include "CardGraveMenu.h"

HRESULT CardGraveMenu::init()
{
	_back = IMAGEMANAGER->addDImage("_darkBackground", L"img/UI/DarkBack.png", WINSIZEX, WINSIZEY);

	_cards = DECKMANAGER->getCardGrave();

	for (int i = 0; i < _cards.size(); i++) {
		int width = i % 5;
		int height = i / 5;

		_cards[i]->setX(400 + width * 225);
		_cards[i]->setY(200 + height * 300);
	}

	UIMANAGER->setOpen(true);

	return S_OK;
}

void CardGraveMenu::release()
{
}

void CardGraveMenu::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		UIMANAGER->changeMenu("null");

	for (int i = 0; i < _cards.size(); i++)
		_cards[i]->update();
}

void CardGraveMenu::render()
{
	_back->render(0, 0, 0.5);

	for (int i = 0; i < _cards.size(); i++) {
		_cards[i]->render();
	}
}

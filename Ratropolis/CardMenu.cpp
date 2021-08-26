#include "stdafx.h"
#include "CardMenu.h"
#include "Player.h"

CardMenu::CardMenu(int type)
{
	_type = type;

	_back = IMAGEMANAGER->addDImage("darkBackground", L"img/UI/DarkBack.png", WINSIZEX, WINSIZEY);
}

CardMenu::~CardMenu()
{
}

HRESULT CardMenu::init()
{
	_scrollY = 0;
	_hide = true;

	_cursor = GAMEMANAGER->getPlayer()->getCursor();
	_card = NULL;

	switch (_type) {
		//ī�� ����
	case 1:
		_cards = DECKMANAGER->getCardBag();
		break;
		//ī�� ����
	case 2:
		_cards = DECKMANAGER->getCardGrave();
		break;
		//��� ī��(���� ��)
	default:
		_cards = DECKMANAGER->getCurrentDeck();
		break;
	}

	//ī���ȣ������ ����
	sort(_cards.begin(), _cards.end(), compare);

	UIMANAGER->setOpen(true);

	return S_OK;
}

void CardMenu::release()
{
	for (int i = 0; i < _cards.size(); i++) {
		_cards[i]->setX(5000);
		_cards[i]->setY(500);

		_cards[i]->setZoom(1.0);
	}
}

void CardMenu::update()
{
	_cursor->updatePosition(_ptMouse.x, _ptMouse.y + _scrollY);
	_cursor->update();

	if (_hide) {
		//ī�� ��ġ ����
		for (int i = 0; i < _cards.size(); i++) {
			int width = i % 5;
			int height = i / 5;

			_cards[i]->setX(400 + width * 225);
			_cards[i]->setY(200 + height * 300);

			_cards[i]->setZoom(1.0);
			_cards[i]->update();
			_cards[i]->setUsable(false);

			//�浹 �˻�
			if (COLLISIONMANAGER->cardListWithCursor(_cards[i], _cursor->getX(), _cursor->getY())) {
				_card = _cards[i];
				_card->setZoom(1.5);
			}
		}
	}
}

void CardMenu::render()
{
	_back->render(0, _scrollY, 0.8);

	//ī�� render
	for (int i = 0; i < _cards.size(); i++) {
		if (_cards[i] == _card) continue;

		_cards[i]->render();
	}

	if (_hide) {
		if (_card) _card->render();
	}
	else {
		_back->render(0, _scrollY, 0.8);

		//ī�� �󼼼���
		_card->setX(WINSIZEX / 2);
		_card->setY(WINSIZEY / 2 + _scrollY);

		_card->setZoom(2.0);
		_card->update();
		_card->setUsable(false);

		_card->render();
		_card->renderDetailed();
	}

	//Ŀ�� render
	_cursor->render();
}

void CardMenu::changeScroll(float num)
{
	Menu::changeScroll(num);

	if (_cards.size() <= 15) {
		_scrollY = 0;
		return;
	}


	//����
	int height = (_cards.size() - 1) / 5 - 2;

	if (_scrollY < 0)
		_scrollY = 0;
	else if (_scrollY >= height * 300)
		_scrollY = height * 300;
}

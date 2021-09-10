#include "stdafx.h"
#include "ShopMenu.h"

ShopMenu::ShopMenu()
{
	_back = IMAGEMANAGER->addDImage("darkBackground", L"img/UI/DarkBack.png", WINSIZEX, WINSIZEY);

	//이미지
	//_shopFrame = IMAGEMANAGER->addDImage("shopFrame", L"img/event/Shop_Pannel.png", WINSIZEX, WINSIZEY);
	_shopFrame = IMAGEMANAGER->addDImage("shopFrame", L"img/UI/menu/shop/Shop_Pannel2.png", 1300, 1000);
	_goldIcon = IMAGEMANAGER->addDImage("shop_goldIcon", L"img/UI/menu/shop/UI_Icon_Economy.png", 40, 40);
	_soldOut = IMAGEMANAGER->addDImage("shop_soldOut", L"img/UI/menu/shop/Sold_Out.png", 150, 75);


	//버튼
	_exit.icon = IMAGEMANAGER->addDImage("shop_exit", L"img/UI/menu/shop/ExitColorBox.png", 87, 83);
	_exit.x = 1400;
	_exit.y = 210;
	_exit.body = RectMakeCenter(_exit.x, _exit.y, _exit.icon->getWidth(), _exit.icon->getHeight());

	_reroll.icon = IMAGEMANAGER->addDImage("shop_reroll", L"img/UI/menu/shop/ShopRerollBtn.png", 87, 83);
	_reroll.x = 1400;
	_reroll.y = 300;
	_reroll.body = RectMakeCenter(_reroll.x, _reroll.y, _reroll.icon->getWidth(), _reroll.icon->getHeight());

	_buttonHL = IMAGEMANAGER->addDImage("shop_buttonHL", L"img/UI/menu/shop/UI_Exit_OutGlow.png", 95, 90);

	_sellingCards.push_back(1);
	_sellingCards.push_back(3);
	_sellingCards.push_back(18);
	_sellingCards.push_back(31);
	_sellingCards.push_back(32);
}

ShopMenu::~ShopMenu()
{
}

HRESULT ShopMenu::init()
{
	if (!_hide) {
		_rollable = true;

		makeCard();
	}	

	_scrollY = 0;

	_cursor = GAMEMANAGER->getPlayer()->getCursor();

	_card = NULL;
	_gold = GAMEMANAGER->getPlayer()->getDefaultStat().gold;

	UIMANAGER->setOpen(true);

	SOUNDMANAGER->play("shopOpen");

	return S_OK;
}

void ShopMenu::release()
{
	if (_hide) return;

	for (int i = 0; i < 8; i++) {
		if (_cardCost[i] == 0) continue;

		SAFE_DELETE(_cardList[i]);
	}
	
	_card = NULL;
	_cardList.clear();
	_num = 0;
}

void ShopMenu::update()
{
	_cursor->updatePosition(_ptMouse.x, _ptMouse.y + _scrollY);
	_cursor->controlMouseShop();

	if (_card) {
		_card->setZoom(1.0);
		_card->setUsable(false);
	}
	//충돌 검사
	for (int i = 0; i < _cardList.size(); i++) {
		if (_cardCost[i] == 0) continue;

		if (_card = COLLISIONMANAGER->cardListWithCursor(_cardList[i], _cursor->getX(), _cursor->getY())) {
			_card->setZoom(1.25);
			if(_gold >= _cardCost[i])
				_card->setUsable(true);
			_selectedCard = i;

			break;
		}
	}

	COLLISIONMANAGER->buttonWithCursor(&_exit, _cursor->getX(), _cursor->getY());
	if (_rollable)
		COLLISIONMANAGER->buttonWithCursor(&_reroll, _cursor->getX(), _cursor->getY());
}

void ShopMenu::render()
{
	_back->render(0, 0, 0.8);

	_shopFrame->render(WINSIZEX / 2 - _shopFrame->getWidth() / 2, WINSIZEY / 2 - _shopFrame->getHeight() / 2 - 50);
	//버튼
	if(_exit.activate)
		_buttonHL->render(_exit.x - _buttonHL->getWidth() / 2, _exit.y - _buttonHL->getHeight() / 2);
	_exit.icon->render(_exit.x - _exit.icon->getWidth() / 2, _exit.y - _exit.icon->getHeight() / 2);
	if (_reroll.activate)
		_buttonHL->render(_reroll.x - _buttonHL->getWidth() / 2, _reroll.y - _buttonHL->getHeight() / 2);
	_reroll.icon->render(_reroll.x - _reroll.icon->getWidth() / 2, _reroll.y - _reroll.icon->getHeight() / 2);

	D2D1_RECT_F tmpRECT;
	WCHAR tmp[128];

	//상점 이름
	swprintf_s(tmp, L"카드 구매 %d/8", _num);
	DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
	tmpRECT = dRectMake(WINSIZEX / 2 - 100, WINSIZEY / 2 - 420, 250, 50);
	DTDMANAGER->printText(tmp, tmpRECT, 40, true, true, true);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(tmpRECT);

	for (int i = 0; i < _cardList.size(); i++) {
		_cardList[i]->render();

		//이미 팔림
		if (_cardCost[i] == 0) {
			DTDMANAGER->setRotate(-20, _cardList[i]->getX(), _cardList[i]->getY());
			_soldOut->render(_cardList[i]->getX() - _soldOut->getWidth() / 2, _cardList[i]->getY() - _soldOut->getHeight() / 2);
			DTDMANAGER->resetTransform();
		}
		//안 팔림
		else {
			_goldIcon->render(_cardList[i]->getX() - 50, _cardList[i]->getBody().bottom + 5);

			swprintf_s(tmp, L"%d", _cardCost[i]);

			DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
			tmpRECT = dRectMake(_cardList[i]->getX() + 5 + 1, _cardList[i]->getBody().bottom + 5 + 1, 200, 50);
			DTDMANAGER->printText(tmp, tmpRECT, 25, false, true);

			DTDMANAGER->setBrushColor(ColorF(ColorF::Goldenrod));
			tmpRECT = dRectMake(tmpRECT.left - 1, tmpRECT.top - 1, 200, 50);
			DTDMANAGER->printText(tmp, tmpRECT, 25, false, true);
		}
	}

	_cursor->render();
}

void ShopMenu::changeScroll(float num)
{
	//카드 추가(카드를 삼)
	if (_card) {
		if (_gold >= _cardCost[_selectedCard]) {
			//골드 차감
			GAMEMANAGER->getPlayer()->changeGold(-_cardCost[_selectedCard]);
			_gold -= _cardCost[_selectedCard];

			//카드 추가
			Card* card = DICTIONARY->makeCard(_card->getCardStat()->number, _card->getCardStat()->level);
			card->init();
			DECKMANAGER->addCard2Deck(card);
			_cardCost[_selectedCard] = 0;
			_num--;

			//리롤 못함
			_rollable = _reroll.activate = false;
		}
	}

	if (_exit.activate) {

		UIMANAGER->changeMenu("null");
	}
	else if (_reroll.activate) {
		//리롤
		release();

		makeCard();
		_card = NULL;

		_rollable = _reroll.activate = false;
	}
}

void ShopMenu::makeCard()
{
	//카드 생성
	for (int i = 0; i < 8; i++) {
		Card* card = DICTIONARY->makeCard(_sellingCards[RND->getInt(5)], RND->getInt(2) + 1);
		card->init();
		_cardList.push_back(card);
		_num++;

		//비용산정 어케하냐, 레어도랑 카트 타입에 따라서 다르게?
		_cardCost[i] = RND->getFromIntTo(50 * card->getCardStat()->level, 70 * card->getCardStat()->level);
	}

	//카드 정렬
	for (int i = 0; i < 8; i++) {
		int width = i % 4;
		int height = i / 4;

		_cardList[i]->setX(440 + width * 250);
		_cardList[i]->setY(325 + height * 325);

		//_cardList[i]->setZoom(1.0);
		_cardList[i]->update();
		_cardList[i]->setUsable(false);
	}
}

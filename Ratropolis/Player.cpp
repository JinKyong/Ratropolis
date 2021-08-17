#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	_cursor = new Cursor;
	_cursor->init(this);

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	//testKey
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1)) {
		changeGold(-5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD2)) {
		changeGold(+5);
	}

	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 5) {
		changeGold(_defaultStat.tax);
		_count = 0;
	}
	

	//조작키
	//controlMouse();
	_cursor->updatePosition(_ptMouse.x, _ptMouse.y);
	_cursor->update();

	if (_selectedCard) {
		_selectedCard->setX(_ptMouse.x);
		_selectedCard->setY(_ptMouse.y);
	}

	controlKeyboard();
}

void Player::render()
{
	_cursor->render();
}

void Player::playGame()
{
	//기본 스탯 설정
	_defaultStat.gold = 70;
	_defaultStat.prize = 0;
	_defaultStat.tax = 5;
	_defaultStat.currentCivil = 5;
	_defaultStat.maxCivil = 5;
	_defaultStat.wave = 1;

	//지도자 레벨
	_level = 1;

	_selectedCard = NULL;

	_count = 0;
}

void Player::controlKeyboard()
{
	//Keyboard

	//Camera Move
	if (KEYMANAGER->isOnceKeyDown(KEY_MAX_LEFT)) {
		_camX = (GAMEMANAGER->getBuildManager()->getLeftWall() + 9) * 90;
	}
	if (KEYMANAGER->isStayKeyDown(KEY_CAM_LEFT) && _camX > _maxLeft + WINSIZEX / 2) {
		_camX -= 20;
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_MAX_RIGHT)) {
		_camX = (GAMEMANAGER->getBuildManager()->getRightWall() - 7) * 90;
	}
	if (KEYMANAGER->isStayKeyDown(KEY_CAM_RIGHT) && _camX < _maxRight - WINSIZEX / 2) {
		_camX += 20;
	}




	//Card
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD1)) {
		if (DECKMANAGER->getCurrentHands().size() >= 1) {
			changeCard(DECKMANAGER->getCurrentHands()[0]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD2)) {
		if (DECKMANAGER->getCurrentHands().size() >= 2) {
			changeCard(DECKMANAGER->getCurrentHands()[1]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD3)) {
		if (DECKMANAGER->getCurrentHands().size() >= 3) {
			changeCard(DECKMANAGER->getCurrentHands()[2]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD4)) {
		if (DECKMANAGER->getCurrentHands().size() >= 4) {
			changeCard(DECKMANAGER->getCurrentHands()[3]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD5)) {
		if (DECKMANAGER->getCurrentHands().size() >= 5) {
			changeCard(DECKMANAGER->getCurrentHands()[4]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD6)) {
		if (DECKMANAGER->getCurrentHands().size() >= 6) {
			changeCard(DECKMANAGER->getCurrentHands()[5]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD7)) {
		if (DECKMANAGER->getCurrentHands().size() >= 7) {
			changeCard(DECKMANAGER->getCurrentHands()[6]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD8)) {
		if (DECKMANAGER->getCurrentHands().size() >= 8) {
			changeCard(DECKMANAGER->getCurrentHands()[7]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD9)) {
		if (DECKMANAGER->getCurrentHands().size() >= 9) {
			changeCard(DECKMANAGER->getCurrentHands()[8]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_CARD10)) {
		if (DECKMANAGER->getCurrentHands().size() >= 10) {
			changeCard(DECKMANAGER->getCurrentHands()[9]);
			_cursor->changeCursor(CURSOR_TYPE_GRAB);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(KEY_DRAW)) {
		if(!_selectedCard)
			DECKMANAGER->redrawCard();
	}
}

void Player::changeMaxRight(int idX)
{
	//_maxRight = CAMERAMANAGER->getBackScreenWidth();
	_maxRight = (idX + 4) * 90;

	if (_maxRight > CAMERAMANAGER->getBackScreenWidth())
		_maxRight = CAMERAMANAGER->getBackScreenWidth();
}

void Player::changeMaxLeft(int idX)
{
	//_maxLeft = 0;
	_maxLeft = (idX - 2) * 90;

	if (_maxLeft < 0)
		_maxLeft = 0;
}

void Player::changeGold(int num)
{
	_defaultStat.gold += num;

	if (_defaultStat.gold >= 99999)
		_defaultStat.gold = 99999;
}

void Player::changePrize(int num)
{
	_defaultStat.prize += num;

	if (_defaultStat.prize >= 99999)
		_defaultStat.prize = 99999;
}

void Player::changeTax(int num)
{
	_defaultStat.tax += num;

	if (_defaultStat.tax >= 99999)
		_defaultStat.tax = 99999;
}

void Player::changeCivil(int num)
{
	_defaultStat.currentCivil += num;

	if (_defaultStat.currentCivil >= _defaultStat.maxCivil)
		_defaultStat.currentCivil = _defaultStat.maxCivil;
}

void Player::changeMaxCivil(int num)
{
	_defaultStat.maxCivil += num;

	if (_defaultStat.maxCivil >= 200)
		_defaultStat.maxCivil = 200;

	changeCivil(num);
}

void Player::cancleCard()
{
	switch (_selectedCard->getCardStat()->type) {
	case CARD_TYPE_BUILD:
		GAMEMANAGER->getBuildManager()->putBcard();
		break;

	default:
		break;
	}

	_selectedCard = NULL;
}

void Player::changeCard(Card * card)
{
	//같은 카드 선택하면 그냥 반환
	if (_selectedCard == card) return;

	//이미 선택되어있을 때 카드를 먼저 놓고
	if (_selectedCard) cancleCard();

	//선택
	_selectedCard = card;

	//선택한 카드가 건물 카드면?
	if (_selectedCard->getCardStat()->type == CARD_TYPE_BUILD)
		GAMEMANAGER->getBuildManager()->grabBcard();
}

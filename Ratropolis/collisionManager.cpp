#include "stdafx.h"
#include "collisionManager.h"
#include "Player.h"
#include "Card.h"

HRESULT collisionManager::init()
{
	_player = GAMEMANAGER->getPlayer();

	return S_OK;
}

void collisionManager::release()
{
}

bool collisionManager::grabbedCard()
{
	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	for (int i = 0; i < hands.size(); i++) {
		if (PtInRect(&(hands[i]->getBody()), _ptMouse)) {
			_player->changeCard(hands[i]);
			hands[i]->setX(_ptMouse.x);
			hands[i]->setY(_ptMouse.y);
			return true;
		}
	}

	return false;
}

void collisionManager::handsWithPlayer()
{
	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	for (int i = 0; i < hands.size(); i++) {
		POINT pt = { _player->getX(), _player->getY() };
		if (PtInRect(&(hands[i]->getBody()), pt)) {
			DECKMANAGER->sortHandsSelect(i);
			return;
		}
	}

	DECKMANAGER->sortHands();
}

void collisionManager::handsWithUseBox(Card* card)
{
	switch (card->getCardStat()->type) {
	case CARD_TYPE_ECONOMY:
		if (PtInRect(&GAMEMANAGER->getUseBox(), _ptMouse))
			card->useCard();
		break;

	default:
		break;
	}
}

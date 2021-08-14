#include "stdafx.h"
#include "collisionManager.h"
#include "Player.h"
#include "Card.h"
#include "Building.h"
#include "MenuHeader.h"

HRESULT collisionManager::init()
{
	_player = GAMEMANAGER->getPlayer();

	return S_OK;
}

void collisionManager::release()
{
}

void collisionManager::buildingsWithCursor(Building* building, float x, float y)
{
	POINT pt = { x, y };
	
	if (PtInRect(&building->getBody(), pt))
		DTDMANAGER->FillRectangle(building->getBody());
}

Card* collisionManager::cardListWithCursor(Card* card, float x, float y)
{
	POINT pt = { x, y };

	if (PtInRect(&card->getBody(), pt))
		return card;

	return NULL;
}

Card * collisionManager::selectedCard(vector<Card*> cards, float x, float y)
{
	POINT pt = { x, y };

	for (int i = 0; i < cards.size(); ++i) {
		if (PtInRect(&cards[i]->getBody(), pt))
			return cards[i];
	}

	return NULL;
}

void collisionManager::handsWithCursor()
{
	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	for (int i = 0; i < hands.size(); i++) {
		//POINT pt = { _player->getX(), _player->getY() };
		if (PtInRect(&(hands[i]->getBody()), _ptMouse)) {
			DECKMANAGER->sortHandsSelect(i);
			return;
		}
	}
}

bool collisionManager::grabbedCard()
{
	if (_player->getCard())	return false;

	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	for (int i = 0; i < hands.size(); i++) {
		if (PtInRect(&(hands[i]->getBody()), _ptMouse)) {
			_player->changeCard(hands[i]);
			return true;
		}
	}

	return false;
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

void collisionManager::buttonWithCursor()
{
	BUTTON* buttons = UIMANAGER->getInGame()->getButton();

	for (int i = 0; i < END_HUD_TYPE; i++) {
		if (PtInRect(&buttons[i].body, _ptMouse)) {
			UIMANAGER->getInGame()->useButton(i);
			break;
		}
	}
}

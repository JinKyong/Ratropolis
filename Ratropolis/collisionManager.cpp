#include "stdafx.h"
#include "collisionManager.h"
#include "Player.h"
#include "Card.h"
#include "BuildManager.h"
#include "InGameMenu.h"
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

bool collisionManager::spaceWithCursor(RECT space, float x, float y)
{
	POINT pt = { x, y };

	if (PtInRect(&space, pt))	return true;

	return false;
}

void collisionManager::selectedButtonSnE(float x, float y)
{
	POINT pt = { x, y };
	PBUTTON shop = GAMEMANAGER->getShopButton();
	PBUTTON event = GAMEMANAGER->getEventButton();

	if (shop->activate) {
		UIMANAGER->changeMenu("shop");
		UIMANAGER->getCurrentMenu()->setHide(true);
		return;
	}

	if (event->activate) {
		EVENTMANAGER->loadEvent(8);
		UIMANAGER->changeMenu("event");
		return;
	}
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

void collisionManager::selectedButtonUI(float x, float y)
{
	POINT pt = { x, y };
	BUTTON* buttons = UIMANAGER->getInGame()->getButton();

	for (int i = 0; i < END_HUD_TYPE; i++) {
		if (PtInRect(&buttons[i].body, pt)) {
			UIMANAGER->getInGame()->useButton(i);
			break;
		}
	}
}

void collisionManager::barWithCursor(float x, float y)
{
	POINT pt = { x, y };

	WaveBar* bar = UIMANAGER->getInGame()->getLeftWave();
	if (PtInRect(&bar->getBody(), pt))
		UIMANAGER->getInGame()->waveLoadingFin();

	bar = UIMANAGER->getInGame()->getRightWave();
	if (PtInRect(&bar->getBody(), pt))
		UIMANAGER->getInGame()->waveLoadingFin();
}

void collisionManager::selectButtonWithCursor(RECT* button, float x, float y)
{
	POINT pt = { x, y };

	EVENTMANAGER->setSelectedButton(-1);
	for (int i = 0; i < 3; i++) {
		if (PtInRect(&button[i], pt)) {
			EVENTMANAGER->setSelectedButton(i);
			break;
		}
	}
}

void collisionManager::handsWithCursor(float x, float y)
{
	POINT pt = { x, y };
	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	for (int i = 0; i < hands.size(); i++) {
		//POINT pt = { _player->getX(), _player->getY() };
		if (PtInRect(&(hands[i]->getBody()), pt)) {
			DECKMANAGER->sortHandsSelect(i);
			return;
		}
	}
}

bool collisionManager::grabbedCard(float x, float y)
{
	if (_player->getCard())	return false;

	POINT pt = { x, y };
	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	for (int i = 0; i < hands.size(); i++) {
		if (PtInRect(&(hands[i]->getBody()), pt)) {
			_player->changeCard(hands[i]);
			return true;
		}
	}

	return false;
}

void collisionManager::handsWithUseBox(Card* card, float x, float y)
{
	POINT pt = { x, y };

	switch (card->getCardStat()->type) {
	case CARD_TYPE_ECONOMY:
		if (PtInRect(&GAMEMANAGER->getUseBox(), pt))
			card->useCard();
		break;

	case CARD_TYPE_BUILD:
		if (GAMEMANAGER->getBuildManager()->getPossible())
			card->useCard();
		else
			GAMEMANAGER->getBuildManager()->putBcard();
		break;

	default:
		break;
	}
}

void collisionManager::buttonWithCursor(PBUTTON button, float x, float y)
{
	POINT pt = { x, y };

	if (PtInRect(&button->body, pt))
		button->activate = true;
	else
		button->activate = false;
}

#include "stdafx.h"
#include "Building.h"
#include "Player.h"

HRESULT Building::init(int idX)
{
	_idX = idX;
	_body = RectMake(_idX * EACH_SPACE, GROUND - _bodyImage->getHeight(), _space * EACH_SPACE, _bodyImage->getHeight());

	return S_OK;
}

HRESULT Building::init(int * reward)
{
	_reward = reward;

	return S_OK;
}

void Building::release()
{
	GAMEMANAGER->getPlayer()->changeGold(-_reward[REWARD_TYPE_GOLD]);
	GAMEMANAGER->getPlayer()->changePrize(-_reward[REWARD_TYPE_PRIZE]);
	GAMEMANAGER->getPlayer()->changeTax(-_reward[REWARD_TYPE_TAX]);
	GAMEMANAGER->getPlayer()->changeMaxCivil(-_reward[REWARD_TYPE_CIVIL]);
}

void Building::update()
{
}

void Building::render()
{
	_bodyImage->render(_idX * EACH_SPACE, GROUND - _bodyImage->getHeight());

	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];

		swprintf_s(tmp, L"idX : %d", _idX);
		DTDMANAGER->printText(tmp, _body.left + 50, _body.top - 30, 100, 50);

		DTDMANAGER->Rectangle(_body);
	}
}

void Building::preview()
{
	_bodyImage->render(_idX * EACH_SPACE, GROUND - _bodyImage->getHeight(), 0.5);
}

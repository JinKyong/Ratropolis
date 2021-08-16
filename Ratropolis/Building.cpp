#include "stdafx.h"
#include "Building.h"
#include "Player.h"

HRESULT Building::init(int idX)
{
	_idX = idX;
	_body = RectMake(_idX * EACH_SPACE, GROUND - _bodyImage->getHeight(), _space * EACH_SPACE, _bodyImage->getHeight());

	//건물 생성 이펙트
	char tmp[128];
	sprintf_s(tmp, "buildEffect%d", _space);
	_buildEffect = IMAGEMANAGER->findDImage(tmp);
	_buildSign = IMAGEMANAGER->findDImage("buildSign");

	_count = 0;
	_onBuild = false;

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
	if (_onBuild) {
		_count += TIMEMANAGER->getElapsedTime();
		if (_count >= BUILD_COUNT) {
			_onBuild = false;
			_count = 0;

			addReward();
			GAMEMANAGER->getBuildManager()->expandSpace(_idX);
		}
	}
}

void Building::render()
{
	if (_onBuild) {
		_buildEffect->render(_idX * EACH_SPACE, GROUND - _buildEffect->getHeight());
		_buildSign->render(_idX * EACH_SPACE + EACH_SPACE / 2 - _buildSign->getWidth() / 2, GROUND - _buildSign->getHeight());
	}
	else
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

void Building::addReward()
{
	GAMEMANAGER->getPlayer()->changeGold(_reward[REWARD_TYPE_GOLD]);
	GAMEMANAGER->getPlayer()->changePrize(_reward[REWARD_TYPE_PRIZE]);
	GAMEMANAGER->getPlayer()->changeTax(_reward[REWARD_TYPE_TAX]);
	GAMEMANAGER->getPlayer()->changeMaxCivil(_reward[REWARD_TYPE_CIVIL]);
}

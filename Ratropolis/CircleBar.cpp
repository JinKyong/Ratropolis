#include "stdafx.h"
#include "CircleBar.h"
#include "Player.h"

HRESULT CircleBar::init(int cost, float duration, int* reward)
{
	//image
	_backBar = IMAGEMANAGER->addDImage("circleBar_back", L"img/UI/CircleGauge_FrameNew.png", 100, 100);
	_frontBar = IMAGEMANAGER->addDImage("circleBar_front", L"img/UI/CircleGauge_Gauge_G.png", 100, 100);
	char tmp[128];
	sprintf_s(tmp, "UI_illuste%d", GAMEMANAGER->getPlayer()->getCard()->getCardStat()->number);
	_image = IMAGEMANAGER->findDImage(tmp);

	//others
	_cost = cost;
	_elapsedTime = 0;
	_duration = duration;
	_reward = reward;

	_fin = false;

	return S_OK;
}

void CircleBar::release()
{
}

void CircleBar::update()
{
	if (_elapsedTime < _duration) {
		_elapsedTime += TIMEMANAGER->getElapsedTime();

		if (_elapsedTime >= _duration) {
			//시민 코스트 돌려주기
			GAMEMANAGER->getPlayer()->changeCivil(_cost);

			//보상
			GAMEMANAGER->getPlayer()->changeGold(_reward[REWARD_TYPE_GOLD]);
			GAMEMANAGER->getPlayer()->changeMaxCivil(_reward[REWARD_TYPE_CIVIL]);
			//GAMEMANAGER->getPlayer()->changeGold(_reward[REWARD_TYPE_DRAW]);
			//GAMEMANAGER->getPlayer()->changeGold(_reward[REWARD_TYPE_UPGRADE]);

			_elapsedTime = _duration;
			_fin = true;
		}
	}
}

void CircleBar::render(float x, float y)
{
	_image->render(x - _image->getWidth() / 2, y - _image->getHeight() / 2);
	_backBar->render(x - _backBar->getWidth() / 2, y - _backBar->getHeight() / 2);

	float ratio = _elapsedTime / _duration;
	_frontBar->render(x - _frontBar->getWidth() / 2 + 10, y + _frontBar->getHeight() / 2 - 10 - (_frontBar->getHeight() - 20) * ratio,
		10, _frontBar->getHeight() - 10 - (_frontBar->getHeight() - 20) * ratio, _frontBar->getWidth() - 20, (_frontBar->getHeight() - 20) * ratio);

}
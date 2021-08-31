#include "stdafx.h"
#include "WaveBar.h"

HRESULT WaveBar::init(int direct, bool boss)
{
	//image
	_backBar = IMAGEMANAGER->addDImage("waveBar_back", L"img/component/progressBar/CircleGauge_Frame_Dark2.png", 100, 100);
	_frontBar = IMAGEMANAGER->addDImage("waveBar_front", L"img/component/progressBar/CircleGauge_Gauge_R.png", 100, 100);
	if (boss)
		_image = IMAGEMANAGER->addDImage("waveBar_bossIcon", L"img/component/progressBar/NormalIcon.png", 50, 50);
	else
		_image = IMAGEMANAGER->addDImage("waveBar_icon", L"img/component/progressBar/EasyIcon.png", 50, 50);

	//others
	_elapsedTime = 0;
	_duration = 10;

	//position
	if (direct)
		_x = 70;
	else
		_x = WINSIZEX - 70;
	_y = WINSIZEY / 2 + 50;
	_body = RectMakeCenter(_x, _y, _backBar->getWidth(), _backBar->getHeight());
	_zoom = 1.0;


	_fin = false;

	return S_OK;
}

void WaveBar::release()
{
}

void WaveBar::update()
{
	if (_elapsedTime < _duration) {
		_elapsedTime += TIMEMANAGER->getElapsedTime();

		if (_elapsedTime >= _duration)
			_fin = true;
	}
}

void WaveBar::render()
{
	_backBar->render(_x - _backBar->getWidth() / 2, _y - _backBar->getHeight() / 2);
	_image->render(_x - _image->getWidth() / 2, _y - _image->getHeight() / 2);

	float ratio = _elapsedTime / _duration;
	_frontBar->render(_x - _frontBar->getWidth() / 2 + 10, _y + _frontBar->getHeight() / 2 - 10 - (_frontBar->getHeight() - 20) * ratio,
		10, _frontBar->getHeight() - 10 - (_frontBar->getHeight() - 20) * ratio, _frontBar->getWidth() - 20, (_frontBar->getHeight() - 20) * ratio);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_body);
}

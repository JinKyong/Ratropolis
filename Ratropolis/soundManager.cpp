#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
	: _system(nullptr),
	_channel(nullptr),
	_sound(nullptr)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//FMOD 엔진 초기화
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*)  * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);
	

	return S_OK;
}

void soundManager::release()
{
	_system->release();
	_system->close();

	delete[] _sound;
	delete[] _channel;
}

void soundManager::update()
{
	//FMOD 엔진 내부에 작동을 계속해서 최신화 시켜주려면 update 걸어두자
	_system->update();
}

void soundManager::registerSound()
{
	//카드 효과음
	addSound("useCard", "sound/SFX_Card_Throw.wav", false, false);
	addSound("useCard31", "sound/SFX_Card_031.wav", false, false);
	addSound("useCard32", "sound/SFX_Card_032.wav", false, false);
	addSound("activeCard", "sound/SFX_Card_Active.wav", false, true);
	addSound("drawCard", "sound/SFX_Card_Draw.wav", false, false);
	addSound("drawCardReady", "sound/SFX_Card_DrawReady.wav", false, false);


	//건물 효과음
	addSound("startConstruct", "sound/SFX_Building_Construction_1.wav", false, false);
	addSound("endConstruct", "sound/SFX_Building_Construction_2.wav", false, false);
	addSound("demolisher", "sound/SFX_Building_Demolisher.wav", false, false);


	//카드 리스트 효과음
	addSound("dictOpen", "sound/SFX_UI_Dictionary_Open.wav", false, false);
	addSound("dictClose", "sound/SFX_UI_Dictionary_Close.wav", false, false);
	addSound("dictSelect", "sound/SFX_UI_Dictionary_Select.wav", false, false);


	//스탯 변동 효과음
	addSound("getGold", "sound/SFX_Effect_GoldGet.wav", false, false);
	addSound("buy", "sound/SFX_UI_Buy.wav", false, false);


	//맵 사운드
	addSound("mainTheme", "sound/BGM_MainTheme.wav", true, true);
	addSound("dessert", "sound/BGM_Dessert.wav", true, true);


	//커서 효과음


	//이벤트 효과음
	addSound("shopArrive", "sound/SFX_Effect_Merchant_Arrived.wav", false, false);
	addSound("shopOpen", "sound/SFX_Effect_Merchant_Click.wav", false, false);
	addSound("shopLeave", "sound/SFX_Effect_Merchant_Leave.wav", false, false);
	addSound("eventArrive", "sound/SFX_Effect_Event_Arrived.wav", false, false);
	addSound("eventOpen", "sound/SFX_Effect_Event_Click.wav", false, false);
	addSound("eventLeave", "sound/SFX_Effect_Event_Leave.wav", false, false);
	addSound("waveStart", "sound/SFX_UI_WaveStart.wav", false, false);
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

unsigned int soundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	unsigned int time = 0;

	bool isPlay;
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getLength(&time, FMOD_TIMEUNIT_MS);
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}

	return time;
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

void soundManager::setVolume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

unsigned int soundManager::getLength(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	unsigned int time = 0;

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getLength(&time, FMOD_TIMEUNIT_MS);

			return time;
		}
	}

	return time;
}

void soundManager::setPosition(string keyName, unsigned int position)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(position, FMOD_TIMEUNIT_MS);

			break;
		}
	}
}

unsigned int soundManager::getPosition(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int position = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&position, FMOD_TIMEUNIT_MS);
			return position;
		}
	}

	return position;
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}

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

	//곡 등록
	registerSound();
	

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
	//addSound("beginning", "music/Beginning of the Journey.mp3",	true, false);
	//addSound("castle", "music/Hyrule Castle.mp3", true, false);
	//이펙트 사운드
	addSound("DefaultAttack", "sound/DefaultAttack.mp3", false, false);		//평타
	addSound("hitDamage", "sound/hitDamage.mp3", false, false);				//데미지받음
	addSound("LevelUp", "sound/LevelUp.mp3", false, false);					//레벨업
	addSound("PickUp", "sound/PickUp.mp3", false, false);					//템줍기
	addSound("Complete", "sound/Complete1.mp3", false, false);				//보스클리어

	addSound("Index", "sound/index.mp3", false, false);						//선택창 이동
	addSound("Select", "sound/select.mp3", false, false);					//선택
	addSound("Cancel", "sound/cancel.mp3", false, false);					//취소
	addSound("Option", "sound/option.mp3", false, false);					//옵션창(UI)

	addSound("FireBlast", "sound/FireBlast.mp3", false, false);
	addSound("Gust", "sound/Gust.mp3", false, false);
	addSound("Lightning", "sound/Lightning.mp3", false, false);
	addSound("RockSlide", "sound/RockSlide.mp3", false, false);
	addSound("DynamicPunch", "sound/DynamicPunch.mp3", false, false);
	addSound("LeafBlade", "sound/LeafBlade.mp3", false, false);
	addSound("ThunderFang", "sound/ThunderFang.mp3", false, false);
	addSound("IceFang", "sound/IceFang.mp3", false, false);
	addSound("FireFang", "sound/FireFang.mp3", false, false);
	addSound("Pound", "sound/Pound.mp3", false, false);

	addSound("Powder", "sound/Powder.mp3", false, false);
	addSound("MetalClaw", "sound/MetalClaw.mp3", false, false);
	addSound("Bind", "sound/Bind.mp3", false, false);
	addSound("CrossChop", "sound/CrossChop.mp3", false, false);
	addSound("FeintAttack", "sound/FeintAttack.mp3", false, false);
	addSound("RockSmash", "sound/RockSmash.mp3", false, false);
	addSound("ShadowClaw", "sound/ShadowClaw.mp3", false, false);
	addSound("TriAttack", "sound/TriAttack.mp3", false, false);

	addSound("WakeUpSlap", "sound/WakeUpSlap.mp3", false, false);
	addSound("WingAttack", "sound/WingAttack.mp3", false, false);
	addSound("VineWhip", "sound/VineWhip.mp3", false, false);
	addSound("Waterfall", "sound/Waterfall.mp3", false, false);
	addSound("SheerCold", "sound/SheerCold.mp3", false, false);
	addSound("DracoMeteor", "sound/DracoMeteor.mp3", false, false);

	//맵 사운드
	addSound("Mt.Bristle", "sound/Field/Mt.Bristle0.mp3", true, true);
	addSound("Concealed Ruins", "sound/Field/Concealed Ruins1.mp3", true, true);
	addSound("Amp Plains", "sound/Field/Amp Plains2.mp3", true, true);
	addSound("Brine Cave", "sound/Field/Brine Cave3.mp3", true, true);
	addSound("Waterfall Cave", "sound/Field/Waterfall Cave4.mp3", true, true);
	addSound("Apple Woods", "sound/Field/Apple Woods5.mp3", true, true);
	addSound("Craggy Coast", "sound/Field/Craggy Coast6.mp3", true, true);
	addSound("Mt.Horn", "sound/Field/Mt.Horn7.mp3", true, true);

	//기타 사운드
	addSound("mainBGM", "sound/other/mainBGM.mp3", true, true);
	addSound("select", "sound/other/dungeonSelect.mp3", true, true);
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

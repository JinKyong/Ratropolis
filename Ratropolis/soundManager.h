#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 50
#define EXTRACHANNELBUFFER 10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;

	typedef map<string, Channel**>			 arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;

private:
	System*		_system;
	Sound**		_sound;
	Channel**	_channel;

	arrSounds	_mTotalSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	void registerSound();
	void addSound(string keyName, string soundName, bool bgm, bool loop);

	unsigned int play(string keyName, float volume = 1.0f);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	void setVolume(string keyName, float volume);
	unsigned int getLength(string keyName);
	void setPosition(string keyName, unsigned int position);
	unsigned int getPosition(string keyName);

	//È£¿Á½ÃÀÌ ¾µ±îºÁ ¸¸µé¾îµÒ
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
};


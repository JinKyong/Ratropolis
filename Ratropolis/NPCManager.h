#pragma once
#include "NPCHeader.h"
#include <vector>

class NPCManager
{
private:
	typedef vector<NPC*>				NPCList;
	typedef vector<NPC*>::iterator		NPCIter;

private:
	NPCList _NPCs;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};
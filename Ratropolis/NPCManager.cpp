#include "stdafx.h"
#include "NPCManager.h"

HRESULT NPCManager::init()
{

	return S_OK;
}

void NPCManager::release()
{
	NPCIter NPC = _NPCs.begin();
	for (; NPC != _NPCs.end();) {
		SAFE_RELEASE(*NPC);
		NPC = _NPCs.erase(NPC);
	}

	_NPCs.clear();
}

void NPCManager::update()
{
	NPCIter NPC = _NPCs.begin();
	for (; NPC != _NPCs.end(); ++NPC)
		(*NPC)->update();
}

void NPCManager::render()
{
	NPCIter NPC = _NPCs.begin();
	for (; NPC != _NPCs.end(); ++NPC)
		(*NPC)->render();
}

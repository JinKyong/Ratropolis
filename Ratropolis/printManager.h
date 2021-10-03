#pragma once
#include "singletonBase.h"

class printManager : public singletonBase<printManager>
{
private:
	bool _debug;

	printManager() {};
	friend singletonBase<printManager>;

public:
	HRESULT init();
	void release();

	void setDebug(bool debug) { _debug = debug; }
	bool isDebug() { return _debug; }
};

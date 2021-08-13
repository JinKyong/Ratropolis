#pragma once
#include "Attribute.h"

class Labor : public Attribute
{
private:

public:
	virtual HRESULT init(int value = 0, float duration = 0);
	virtual void release();
	virtual void update();
	virtual void render();
};


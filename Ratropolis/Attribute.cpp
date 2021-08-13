#include "stdafx.h"
#include "Attribute.h"

HRESULT Attribute::init(int value, float duration)
{
	_value = value;
	_duration = duration;

	return S_OK;
}

void Attribute::release()
{
}

void Attribute::update()
{
}

void Attribute::render()
{
}

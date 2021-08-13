#include "stdafx.h"
#include "Labor.h"
#include "ToolTip.h"

HRESULT Labor::init(int value, float duration)
{
	Attribute::init(value, duration);

	_type = ATTRIBUTE_TYPE_LABOR;

	_toolTip = new ToolTip;
	_toolTip->init(L"노동", L"효과가 지속되는 동안 시민 사용이 제한됩니다.");

	return S_OK;
}

void Labor::release()
{
}

void Labor::update()
{
	Attribute::update();
}

void Labor::render()
{
}

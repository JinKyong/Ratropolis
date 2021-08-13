#include "stdafx.h"
#include "Labor.h"
#include "ToolTip.h"

HRESULT Labor::init(int value, float duration)
{
	Attribute::init(value, duration);

	_type = ATTRIBUTE_TYPE_LABOR;

	_toolTip = new ToolTip;
	_toolTip->init(L"�뵿", L"ȿ���� ���ӵǴ� ���� �ù� ����� ���ѵ˴ϴ�.");

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

#include "stdafx.h"
#include "Labor.h"
#include "ToolTip.h"

HRESULT Labor::init()
{
	ToolTip::init();

	_name = L"�뵿";
	_desc = L"ȿ���� ���ӵǴ� ���� �ù� ����� ���ѵ˴ϴ�.";

	return S_OK;
}

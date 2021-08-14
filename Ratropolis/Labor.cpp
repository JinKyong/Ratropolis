#include "stdafx.h"
#include "Labor.h"
#include "ToolTip.h"

HRESULT Labor::init()
{
	ToolTip::init();

	_name = L"노동";
	_desc = L"효과가 지속되는 동안 시민 사용이 제한됩니다.";

	return S_OK;
}

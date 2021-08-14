#include "stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(float x, float y)
{
	_x = x;
	_y = y;

	_fin = false;

	return S_OK;
}

void ProgressBar::release()
{
}

void ProgressBar::update()
{
}

void ProgressBar::render()
{
}
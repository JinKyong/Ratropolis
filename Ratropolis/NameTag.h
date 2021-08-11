#pragma once

class NameTag
{
private:
	dImage* _image;

	LPWSTR _name;

public:
	HRESULT init(LPCWCHAR name);
	void render(float x, float y);
};


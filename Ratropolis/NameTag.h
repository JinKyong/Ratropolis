#pragma once

class NameTag
{
private:
	dImage* _image;

	LPWSTR _name;
	int _level;

public:
	HRESULT init(LPCWCHAR name, int level);
	void render(float x, float y);
};


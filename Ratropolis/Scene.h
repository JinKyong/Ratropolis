#pragma once
#include <vector>

class Scene
{
protected:

public:
	Scene() {};
	~Scene() {};

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void changeScene() = 0;
};
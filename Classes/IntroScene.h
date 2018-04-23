#pragma once
#include "cocos2d.h"
USING_NS_CC;

class IntroScene : public Scene
{
public:
	CREATE_FUNC(IntroScene);

	static Scene* createScene();

	virtual bool init();

	void update(float deltaTime) override;
};


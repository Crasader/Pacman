#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
private:
	static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::Label* label;
	float speed = 2.0f;
	int currentX = 0;
	int currentY = 0;
public:
	CREATE_FUNC(GameScene);

	static cocos2d::Scene* createScene();

	virtual bool init();
	
	virtual bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	void itemClickedCallback(cocos2d::Ref* pSender);

	void update(float deltaTime) override;
};

#endif
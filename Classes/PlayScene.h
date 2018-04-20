#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class PlayScene : public Scene
{
public:
	CREATE_FUNC(PlayScene);

	static Scene* createScene();

	virtual bool init();

	void update(float deltaTime) override;

public:
	PlayScene();
	~PlayScene();
};

#endif // ! __PLAY_SCENE_H__


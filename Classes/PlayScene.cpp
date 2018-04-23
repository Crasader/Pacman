#include "PlayScene.h"
#include "StaticObject.h"
#include <fstream>
#include "MapController.h"

Scene * PlayScene::createScene()
{
	return PlayScene::create();
}

bool PlayScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 topLeft = origin + Vec2(0, visibleSize.height);

	MapController* mapController = MapController::create();
	mapController->loadFile("pacman_map.txt");
	mapController->parseMap();
	mapController->setPosition(topLeft - Vec2(mapController->blockSize, 0));

	this->addChild(mapController);
	this->scheduleUpdate();
	return true;
}

void PlayScene::update(float deltaTime)
{

}

PlayScene::PlayScene()
{

}


PlayScene::~PlayScene()
{

}

#include "IntroScene.h"
#include "PlayScene.h"
#include "StaticStorage.h"

Scene * IntroScene::createScene()
{
	return IntroScene::create();
}

bool IntroScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 center = origin + visibleSize / 2;
	Vec2 topRight = origin + visibleSize;

	auto logo = Sprite::create("sprites/logo.png");
	logo->setScale(1.2f);
	logo->setPosition(Vec2(center.x, topRight.y - logo->getBoundingBox().size.height));
	this->addChild(logo);

	auto label = Label::createWithSystemFont(StaticStorage::stringValue, "Arial", 20);
	label->setAlignment(TextHAlignment::CENTER);
	label->setPosition(Vec2(center.x, origin.y + 45));
	/*label->setScale(3);*/

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		this->getEventDispatcher()->removeAllEventListeners();
		Director::getInstance()->replaceScene(PlayScene::createScene());
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->addChild(label);

	return true;
}

void IntroScene::update(float deltaTime)
{
}

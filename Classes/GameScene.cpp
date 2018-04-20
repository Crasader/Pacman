#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* GameScene::createScene() {
	return GameScene::create();
}


bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	label = Label::createWithSystemFont("Hello", "Arial", 13);
	if (label != nullptr) {
		label->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMinY() + label->getSystemFontSize() / 2);
		this->addChild(label);
	}

	Vec2 spriteOrigin = origin + Vec2(150, visibleSize.height);

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(false);
	
	const int SIZE = 13;
	auto spriteCache = SpriteFrameCache::getInstance();
	auto menu = Menu::create();
	menu->setPosition(origin);
	spriteCache->addSpriteFramesWithFile("sprites/wall.plist");
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 31; j++) {
			char name[100] = { 0 };
			sprintf(name, "pacman [www.imagesplitter.net]-%d-%d.png", i, j);
			SpriteFrame* frame = spriteCache->getSpriteFrameByName(name);

			MenuItemImage* item = MenuItemImage::create();
			item->setNormalSpriteFrame(frame);
			item->setSelectedSpriteFrame(frame);
			item->setCallback([=](Ref* pSender) {
				Sprite* sprite = Sprite::createWithSpriteFrame(frame);
				std::string name = "sprite_" + std::to_string(currentX) + "_" + std::to_string(currentY);
				sprite->setName(name);
				label->setString(name);
				int spriteSize = SIZE * 1.3f;
				sprite->setPosition(spriteOrigin.x + currentX * spriteSize, spriteOrigin.y - spriteSize / 2 - currentY * spriteSize);
				if (++currentX > 26) {
					currentX = 0;
					currentY++;
				}
				sprite->setContentSize(Size(spriteSize, spriteSize));
				this->addChild(sprite);
			});

			item->setContentSize(Size(SIZE, SIZE));
			item->setPosition(origin + Vec2(SIZE / 2, SIZE/2) + Vec2(i, j) * SIZE);
			menu->addChild(item);
		}
	};

	MenuItemImage* back = MenuItemImage::create();
	back->setNormalImage(Sprite::create("CloseNormal.png"));
	back->setSelectedImage(Sprite::create("CloseSelected.png"));
	back->setCallback([=](Ref* pSender) {
		currentX--;
		if (currentX < 0) {
			if (currentY > 0) {
				currentX = 26;
				currentY--;
			}
			else {
				currentX = 0;
			}
		}
		std::string name = "sprite_" + std::to_string(currentX) + "_" + std::to_string(currentY);
		if (this->getChildByName(name) != nullptr) {
			this->removeChildByName(name);
		}
	});
	back->setPosition(origin + Vec2(back->getBoundingBox().getMaxX() / 2, visibleSize.height - back->getBoundingBox().getMaxY() / 2));
	menu->addChild(back);

	this->addChild(menu);

	this->scheduleUpdate();
	
	return true;
}


bool GameScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	return keys.find(keyCode) != keys.end();
}


void GameScene::update(float deltaTime) {

	
}


void GameScene::itemClickedCallback(Ref* pSender) {
	label->setString(((MenuItemSprite*)pSender)->getName());
}


std::map<EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameScene::keys;
#include "StaticObject.h"
#include "MapController.h"

bool StaticObject::initialize(Sprite * sprite)
{
	return initialize(sprite, "");
}

bool StaticObject::initialize(cocos2d::Sprite * sprite, std::string labelText)
{
	return initialize(sprite, labelText, nullptr);
}

bool StaticObject::initialize(cocos2d::Sprite * sprite, std::string labelText, MapController * mapController)
{
	this->sprite = sprite;
	if (this->sprite != nullptr) {
		this->addChild(sprite);
	}
	this->label = Label::createWithSystemFont(labelText, "Arial", 10);
	this->label->setColor(Color3B::RED);
	this->mapController = mapController;
	return true;
}

void StaticObject::setMapController(MapController * mapController)
{
	this->mapController = mapController;
}

void StaticObject::enableLabel(bool enable)
{
	if (enable) {
		this->addChild(label);
	}
	else {
		this->removeChild(label, true);
	}
}

bool StaticObject::isReady()
{
	return mapController != nullptr && mapController->isReady();
}

Animate * StaticObject::getAnimate(std::initializer_list<std::string> frameNames, float delayTime)
{
	Vector<SpriteFrame*> frames;
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	for each (std::string name in frameNames) {
		SpriteFrame* frame = cache->getSpriteFrameByName(name);
		if (frame != nullptr) {
			frames.pushBack(frame);
		}
	}
	Animation* animation = Animation::createWithSpriteFrames(frames, delayTime);
	Animate* animate = Animate::create(animation);
	return animate;
}

void StaticObject::setAnimate(Animate * animate)
{
	if (this->sprite != nullptr && animate != nullptr && animate != currentAnimate) {
		this->sprite->stopAllActions();
		this->sprite->runAction(RepeatForever::create(animate));
		this->currentAnimate = animate;
	}
}

void StaticObject::setAnimate(Animate * animate, std::function<void()> callback)
{
	if (this->sprite != nullptr && animate != nullptr && animate != currentAnimate) {
		this->sprite->stopAllActions();
		auto callFunc = CallFunc::create([=]() { callback(); });
		Sequence* seq = Sequence::create(animate, callFunc, nullptr);
		this->sprite->runAction(seq);
		this->currentAnimate = animate;
		
	}
}

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}

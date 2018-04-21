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

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}

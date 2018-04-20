#include "StaticObject.h"


bool StaticObject::initialize(Sprite * sprite)
{
	return initialize(sprite, "");
}

bool StaticObject::initialize(cocos2d::Sprite * sprite, std::string labelText)
{
	this->sprite = sprite;
	if (this->sprite != nullptr) {
		this->addChild(sprite);
	}
	this->label = Label::createWithSystemFont(labelText, "Arial", 10);
	this->label->setColor(Color3B::RED);
	return true;
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

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}

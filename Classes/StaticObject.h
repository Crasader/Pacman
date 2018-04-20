#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__

#include "cocos2d.h"
USING_NS_CC;

class StaticObject : public Node
{
public:
	Sprite* sprite;
	Label* label;

public:
	CREATE_FUNC(StaticObject);
	virtual bool initialize(cocos2d::Sprite* sprite);
	virtual bool initialize(cocos2d::Sprite* sprite, std::string labelText);
	virtual void enableLabel(bool enable);
	
public:
	StaticObject();
	~StaticObject();
};

#endif // !__STATIC_OBJECT_H__

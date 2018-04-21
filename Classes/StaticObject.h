#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__

#include "cocos2d.h"
USING_NS_CC;

class MapController;

class StaticObject : public Node
{
public:
	Sprite* sprite;
	Label* label;
	MapController* mapController;

public:
	CREATE_FUNC(StaticObject);
	virtual bool initialize(cocos2d::Sprite* sprite);
	virtual bool initialize(cocos2d::Sprite* sprite, std::string labelText);
	virtual bool initialize(cocos2d::Sprite* sprite, std::string labelText, MapController* mapController);

	virtual void setMapController(MapController* mapController);
	virtual void enableLabel(bool enable);
	virtual bool isReady();
public:
	StaticObject();
	~StaticObject();
};

#endif // !__STATIC_OBJECT_H__

#ifndef __KEYBOARD_HANDLER_H__
#define __KEYBOARD_HANDLER_H__

#include "cocos2d.h"
USING_NS_CC;

class KeyboardHandler
{
public:
	std::map<EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keyMap;
	EventListenerKeyboard* eventListener;
	std::vector<std::function<void>> pressCallbackList;
	std::vector<std::function<void>> releaseCallbackList;
public:
	KeyboardHandler();
	~KeyboardHandler();

public:
	virtual void init();
};

#endif
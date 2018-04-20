#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler() {

}


KeyboardHandler::~KeyboardHandler() {

}


void KeyboardHandler::init() {
	eventListener = EventListenerKeyboard::create();
	/*pressCallbackList = new std::vector<std::function<void>>();
	releaseCallbackList = new std::vector<std::function<void>>();*/

	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		for each (auto callback in pressCallbackList)
		{
			callback;
		}
	};
}


#include "Control.h"
#include <string>

Control::Control() {

	// add a event listener for keyboard
	kb_listener = cocos2d::EventListenerKeyboard::create();

	// eventlistener listen for press and release (for polling)
	kb_listener->onKeyPressed = CC_CALLBACK_2(Control::keyPressed, this);

	kb_listener->onKeyReleased = CC_CALLBACK_2(Control::keyReleased, this);
}

void Control::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		// left
		cocos2d::log("Left");
		this->left = true;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// right
		cocos2d::log("Right");
		this->right = true;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		// up
		cocos2d::log("Up");
		this->up = true;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		// down
		cocos2d::log("Down");
		this->down = true;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		// implement shoot here
		this->space = true;
		break;
	}
}


void Control::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*) {
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		// left
		this->left = false;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// right
		this->right = false;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		// up
		this->up = false;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		// down
		this->down = false;
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		// implement shoot here
		this->space = false;
		break;
	}
}


cocos2d::EventListenerKeyboard* Control::get_kb_listener() {
	return kb_listener;
}


bool Control::getUp() const { return up; }
bool Control::getDown() const { return down; }
bool Control::getLeft() const { return left; }
bool Control::getRight() const { return right; }
bool Control::getSpace() const { return space; }

bool Control::isSpacePressed() const
{
	return !wasSpacePressed && space;
}

void Control::resetUp() { up = false; }
void Control::resetDown() { down = false; }
void Control::resetLeft() { left = false; }
void Control::resetRight() { right = false; }

void Control::update()
{
	wasSpacePressed = space;
}

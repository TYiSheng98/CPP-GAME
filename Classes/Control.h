#pragma once

#include "cocos2d.h"

// https://gamefromscratch.com/cocos2d-x-tutorial-series-handling-the-keyboard/

class Control{
private:
	cocos2d::EventListenerKeyboard* kb_listener;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
	bool wasSpacePressed = false;

public:
	Control();

	// checker to check if a key is pressed (for polling)
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	// action to do when key is pressed
	void keyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	// action to do when key is released
	void keyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	cocos2d::EventListenerKeyboard* get_kb_listener();

	bool getUp() const;
	bool getDown() const;
	bool getLeft() const;
	bool getRight() const;
	bool getSpace() const;
	bool isSpacePressed() const;

	void resetUp();
	void resetDown();
	void resetLeft();
	void resetRight();
	
	void update();
};
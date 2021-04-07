#pragma once

#include "cocos2d.h"
#include "Characters/Mob.h"
#include <vector>
#include <chrono>
#include <ctime>

class level_logic {
private:

	cocos2d::Vec2 spawn_point_1 = cocos2d::Vec2(77.0, 72.0);  // bottom left
	cocos2d::Vec2 spawn_point_2 = cocos2d::Vec2(77.0, 642.0); // top left
	cocos2d::Vec2 spawn_point_3 = cocos2d::Vec2(873.0, 642.0); // top right
	cocos2d::Vec2 spawn_point_4 = cocos2d::Vec2(873.0, 72.0); // bottom right

	cocos2d::Vec2 array_of_spawns[4] = { spawn_point_1, spawn_point_2, spawn_point_3, spawn_point_4 };

	int current_level = 0;
public:
	level_logic(int);
	void initialize_level(MainGameScene* world);
	void update_level(int);
};
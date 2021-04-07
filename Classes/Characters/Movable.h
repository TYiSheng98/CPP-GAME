#pragma once

#include "map_piece.h"

class MainGameScene;

class Movable : public map_piece
{
public:
	Movable(double x_axis, double y_axis, const std::string& file_path, float size,
		const std::string& char_type, float maxSpeed);

	virtual void update(MainGameScene* world, float dt);
	std::string get_charType();
protected:
	cocos2d::Vec2 dir;
	float maxSpeed;
	float currSpeed;

private:
	std::string char_type;
};

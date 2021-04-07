#pragma once

#include "Movable.h"
#include "Character.h"

class Bullet : public Movable
{
private:
	float damage;

public:
	Bullet(double x_axis, double y_axis, const std::string& file_path, float size,
		const std::string& char_type, float maxSpeed, const cocos2d::Vec2& dir,
		float damage);

	virtual void update(MainGameScene* world, float dt) override;
};

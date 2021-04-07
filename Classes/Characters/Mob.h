#pragma once

#include "Character.h"

class Hero;

class Mob : public Character
{
public:
	Mob(double x_axis, double y_axis, const std::string& file_path, float size,
		const std::string& char_type, float maxSpeed, float hp, float damage);

	virtual void update(MainGameScene* world, float dt) override;

private:
	void pursue(Hero* hero);
	void attack(Hero* hero, float dt);

private:
	float damage;
};

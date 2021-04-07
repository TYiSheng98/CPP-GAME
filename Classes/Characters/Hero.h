#pragma once
#include <Characters/Character.h>
#include <Control.h>

class Hero : public Character
{
public:
	Hero(double x_axis, double y_axis, const std::string& file_path, float size,
		const std::string& char_type, float maxSpeed, float hp);

	virtual void update(MainGameScene* world, float dt) override;
	bool operator<(float);
private:
	void updateMovement(float dt, const Control& controller);
	void updateWeapon(MainGameScene* world);
};

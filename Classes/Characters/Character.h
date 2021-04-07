#pragma once
#include "cocos2d.h"
#include "movable.h"

class Character : public Movable
{
private:
	float health_point;
	
public:

	Character(double x_axis, double y_axis, const std::string& file_path, float size,
		const std::string& char_type, float maxSpeed, float hp);
		
	float getHealth() const;
	void damage(float dmg);

	virtual void update(MainGameScene* world, float dt) override;
	
private:
	void clampPosition(MainGameScene* world);
	virtual void updateAliveStatus(MainGameScene* world);
};

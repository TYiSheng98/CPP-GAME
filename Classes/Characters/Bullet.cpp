#include "Bullet.h"

#include "MainGameScene.h"

Bullet::Bullet(double x_axis, double y_axis, const std::string& file_path, float sizeValue,
	const std::string& char_type, float maxSpeed, const cocos2d::Vec2& dirValue, float damageValue) :
	Movable(x_axis, y_axis, file_path, sizeValue, char_type, maxSpeed),
	damage(damageValue)
{
	dir = dirValue;
	currSpeed = maxSpeed;
}

void Bullet::update(MainGameScene* world, float dt)
{
	Movable::update(world, dt);

	//if out of play area defined in main then destroy the bullet
	if (!world->getGameArea().containsPoint(getPosition()))
	{
		world->destroyGameObject(this);
		return;
	}

	// if objects are close enough AND the other object is a character then deal damage to it and destroy bullet
	for (auto& movable : world->getGameObjects())
	{
		if (getPosition().distanceSquared(movable->getPosition()) <= (size + movable->getSize()) * (size + movable->getSize()))
		{
			if (auto character = std::dynamic_pointer_cast<Character>(movable))
			{
				character->damage(damage);
				world->destroyGameObject(this);
				return;
			}
		}
	}
}

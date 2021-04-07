#include "Mob.h"

#include "MainGameScene.h"
#include "Hero.h"

Mob::Mob(double x_axis, double y_axis, const std::string& file_path, float sizeValue,
	const std::string& char_type, float maxSpeed, float hp, float damageValue) :
	Character(x_axis, y_axis, file_path, sizeValue, char_type, maxSpeed, hp),
	damage(damageValue)
{

}

void Mob::update(MainGameScene* world, float dt)
{
	Character::update(world, dt);

	pursue(world->getHero());
	attack(world->getHero(), dt);
}

//chase the hero
void Mob::pursue(Hero* hero)
{
	if (!hero)
	{
		currSpeed = 0.0f;
	}
	else
	{
		dir = (hero->getPosition() - getPosition()).getNormalized();
		currSpeed = maxSpeed;
	}
}


void Mob::attack(Hero* hero, float dt)
{
	if (!hero)
	{
		return;
	}
	// ok tldr if in contact then do damage
	if (getPosition().distanceSquared(hero->getPosition()) <= size * size + hero->getSize() * hero->getSize())
	{
		hero->damage(damage * dt);
	}
}

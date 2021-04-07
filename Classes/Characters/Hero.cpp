#include "Characters/Hero.h"

#include "MainGameScene.h"
#include "bullet.h"
#include "AudioEngine.h"

Hero::Hero(double x_axis, double y_axis, const std::string& file_path, float sizeValue,
	const std::string& char_type, float maxSpeed, float hp) :
	Character(x_axis, y_axis, file_path, sizeValue, char_type, maxSpeed, hp)
{

}


void Hero::update(MainGameScene* world, float dt)
{
	updateMovement(dt, world->getController());
	updateWeapon(world);

	Character::update(world, dt);
}


void Hero::updateMovement(float dt, const Control& controller)
{
	cocos2d::Vec2 newDir(0.0f, 0.0f);

	if (controller.getUp())
	{
		newDir.y += 1.0f;
	}
	if (controller.getDown())
	{
		newDir.y -= 1.0f;
	}
	if (controller.getLeft())
	{
		newDir.x -= 1.0f;
	}
	if (controller.getRight())
	{
		newDir.x += 1.0f;
	}

	// if stopped
	if (!newDir.isZero())
	{
		currSpeed = maxSpeed;
		dir = newDir.getNormalized();
	}
	else
	{
		currSpeed = 0.0f;
	}
}

void Hero::updateWeapon(MainGameScene* world)
{
	// when space is pressed, construct a bullet shooting at that direction
	if (world->getController().isSpacePressed())
	{

		int  sv = cocos2d::UserDefault::getInstance()->getIntegerForKey("sound_volume");
		bool st = cocos2d::UserDefault::getInstance()->getBoolForKey("sound_toggle");
		//play shoot sound
		// cocos2d::AudioEngine::preload("music/shoot02.mp3");
		//int sfx_id= cocos2d::AudioEngine::play2d("music/shoot02.mp3");
		cocos2d::AudioEngine::preload("music/laser-shoot.mp3");
		if (st == true) {
			int sfx_id = cocos2d::AudioEngine::play2d("music/laser-shoot.mp3", false, (sv / 100.0f));
			cocos2d::AudioEngine::pause(sfx_id);
		}
		
		// x, y, file, size, speed, vec2d, damage (can update the damage here if going to implement damage up)
		auto bullet = std::make_shared<Bullet>(getPosition().x, getPosition().y,
			"img/bullet.png", 1.0f, "bullet", 150.0f, dir, 1.0f);
		world->instantiateGameObject(bullet);
	}
}

// check if hero is below 0 HP.
bool Hero::operator<(float amount) {
	if (getHealth() <= amount)
		return true;
	else
		return false;
}
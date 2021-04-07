#include "Character.h"
#include "Movable.h"
#include "MainGameScene.h"
#include "AudioEngine.h"

Character::Character(double x_axis, double y_axis, const std::string& file_path, float sizeValue,
	const std::string& char_type, float maxSpeed, float hp) :
	Movable(x_axis, y_axis, file_path, sizeValue, char_type, maxSpeed),
	health_point(hp)
{

}

// getter for health
float Character::getHealth() const
{
	return health_point;
}

// on damage (take the values from mob damage)
void Character::damage(float dmg)
{
	int  sv = cocos2d::UserDefault::getInstance()->getIntegerForKey("sound_volume");
	bool st = cocos2d::UserDefault::getInstance()->getBoolForKey("sound_toggle");
	//play damage sound
	cocos2d::AudioEngine::preload("music/damage.mp3");
	if (st == true) {
		int sfx_id = cocos2d::AudioEngine::play2d("music/damage.mp3", false, (sv / 100.0f));
		/*cocos2d::AudioEngine::pause(sfx_id);*/
	}
	health_point -= dmg;
}


void Character::update(MainGameScene* world, float dt)
{
	Movable::update(world, dt);

	clampPosition(world);
	updateAliveStatus(world);
}

//restrict all obj in map so they wont go out of wall 
void Character::clampPosition(MainGameScene* world)
{
	auto gameArea = world->getGameArea();

	auto pos = getPosition();
	pos.x = cocos2d::clampf(pos.x, gameArea.getMinX() + size / 2.0f, gameArea.getMaxX() - size / 2.0f);
	pos.y = cocos2d::clampf(pos.y, gameArea.getMinY() + size / 2.0f, gameArea.getMaxY() - size / 2.0f);
	setposition(pos);
}

// remove hero when he dead
void Character::updateAliveStatus(MainGameScene* world)
{
	if (health_point <= 0)
	{
		if (this->get_charType() != "hero")
			world->add_score();


		world->destroyGameObject(this);
	}
}

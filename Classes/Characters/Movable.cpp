#include "Movable.h"

#include <string>
#include "MainGameScene.h"

using namespace cocos2d;

// for movable game objs
Movable::Movable(double x_axis, double y_axis, const std::string& file_path, float sizeValue,
	const std::string& charType, float maxSpeedValue) :
	map_piece(x_axis, y_axis, file_path, sizeValue),
	dir(1.0f, 0.0f),
	char_type(charType),
	maxSpeed(maxSpeedValue),
	currSpeed(0.0f)
{

}

//update is called each frame and it changes the position of a 
//game object towards direction dir by 
//currentSpeed distance per second.
void Movable::update(MainGameScene* world, float dt)
{
	dir.normalize();
	setposition(getPosition() + currSpeed * dir * dt);
	
}


std::string Movable::get_charType() {
	return char_type;
}

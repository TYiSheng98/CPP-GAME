#include "cocos2d.h"
#include "map_piece.h"
#include <string>

// contructor of the map piece for objects/sprites on the map
map_piece::map_piece(double x_axis, double y_axis, const std::string& file_path, float sizeValue) :
	position(x_axis, y_axis),
	spriteImg(cocos2d::Sprite::create(file_path)),
	size(sizeValue)
{
	spriteImg->retain();

	// middle of sprite
	spriteImg->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	spriteImg->setPosition(position);
}

//release spriteImg obj
map_piece::~map_piece()
{
	spriteImg->release();
}

//character movement using setposition
void map_piece::setposition(const cocos2d::Vec2 newPos)
{
	position = newPos;

	spriteImg->setPosition(position);
}

const cocos2d::Vec2& map_piece::getPosition() const
{
	return position;
}

cocos2d::Sprite* map_piece::get_sprite()
{
	return spriteImg;
}

float map_piece::getSize() const
{
	return size;
}

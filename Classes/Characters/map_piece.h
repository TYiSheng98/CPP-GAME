#include "cocos2d.h"
#include <string>


class map_piece
{
private:
	cocos2d::Sprite* spriteImg;
	cocos2d::Vec2 position;
protected:
	float size;
public:
	map_piece(double x_axis, double y_axis, const std::string& file_path, float size);
	virtual ~map_piece();
	void setposition(const cocos2d::Vec2 newPos);
	const cocos2d::Vec2& getPosition() const;
	cocos2d::Sprite* get_sprite();
	float getSize() const;
};

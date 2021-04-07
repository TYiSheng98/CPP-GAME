#include "level_logic.h"
#include <stdlib.h>
#include "cocos2d.h"
#include "MainGameScene.h"

level_logic::level_logic(int current_level){
	this->current_level = current_level;

}

void level_logic::initialize_level(MainGameScene* world) {

	for (int i = 0; i < 4; i++) {
		int random_spawn_seed = rand() % (10 + current_level * current_level);

		cocos2d::Vec2 current_spawn = array_of_spawns[i];
		
		for (int j = 0; j < random_spawn_seed; j++) {
			if (j % 2 == 0)
				// x, y, file_path, size, char_type, maxSpeed, hp, damage
				world->instantiateGameObject(std::make_shared<Mob>(current_spawn.x + (j+1), current_spawn.y + (j+1), "char/skeleton.png", 7.0f, "skeleton soldier", 50.0f, 3.0f, 1.0f));
			else
				world->instantiateGameObject(std::make_shared<Mob>(current_spawn.x - (j+1), current_spawn.y - (j+1), "char/demon.png", 7.0f, "demon", 50.0f, 3.0f, 1.0f));
		}
		
	}
}

void level_logic::update_level(int next_level) {
	current_level = next_level;
}

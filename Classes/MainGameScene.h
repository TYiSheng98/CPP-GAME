/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __MainGameScene_SCENE_H__
#define __MainGameScene_SCENE_H__

#include "cocos2d.h"

#include "Characters/Hero.h"
#include "Control.h"
#include "level_logic.h"
#include <chrono>
#include <ctime>


class MainGameScene : public cocos2d::Scene
{

private:
	// for map
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _background;
    
	// for hero movement
	Control controls;
	
	// for hero and mob object creation  
	std::shared_ptr<Hero> hero;
	std::vector<std::shared_ptr<Movable>> gameObjectsToAdd;
	std::vector<std::shared_ptr<Movable>> gameObjects;
	std::vector<Movable*> gameObjectsToDelete;
	
	// for mob spawning
    level_logic* levels;

    // for HUD
    cocos2d::Layer* HUD;
    cocos2d::Camera* cam;
    cocos2d::Label* scorePoints;
    cocos2d::Label* currentLevel;
    std::vector<cocos2d::Sprite*> containerOfHealth;
    
    int current_level = 1;
    int player_score = 0;
    
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> current_time;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // initialize all game objects
    void initializeObjects();

    // create the HUD
    void initializeHUD();
    void updateHUD();
    void add_score();
    int get_current_level();

    // overriding the main updating function for the game scene
    void update(float) override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	const Control& getController() const;	
    cocos2d::Rect getGameArea() const;
    Hero* getHero();

    std::vector<std::shared_ptr<Movable>>& getGameObjects();
    void instantiateGameObject(const std::shared_ptr<Movable>& gameObject);
	void destroyGameObject(Movable* gameObject);	


    // implement the "static create()" method manually
    CREATE_FUNC(MainGameScene);
};

#endif // __MainGameScene_SCENE_H__

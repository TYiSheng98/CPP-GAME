#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

class EndGameScene : public cocos2d::Scene
{

private:
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _background;

public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* createScene(int game_score);

    virtual bool init();

    void txtfieldevent(Ref* sender, TextField::EventType type);

    // a selector callback
    void savepressed(Ref* sender, Button::TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(EndGameScene);
    ;
};
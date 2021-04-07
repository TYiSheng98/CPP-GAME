#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

class OptionsScene : public cocos2d::Scene
{

private:
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _background;

public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* createScene(int bg_music_id,int sfx_id);
    virtual bool init();

    // a selector callback
    void btnpressed(Ref* sender, Button::TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(OptionsScene);

    void sliderEvent(Ref* sender,Slider::TouchEventType type);
;
};
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

#include "MainMenuScene.h"
#include "OptionsScene.h"
#include "GameScene.h"
#include "ScoreboardScene.h"
#include "CreditScene.h"
#include "ControlsScene.h"
#include "EndGameScene.h"

USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //background image
    auto bg = Sprite::create("img/dungeon_bg.jpg");
    float scale = MAX(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
    bg->setScale(scale);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bg, -2);

    //create title label
    
    auto titlelabel = Label::createWithBMFont("craftacular/raw/font-title-export.fnt", "TOMDICKHARRY");
    //titlelabel->setAnchorPoint(Vec2(0, 0));
    titlelabel->setBMFontSize(20);
    titlelabel->setColor(Color3B::YELLOW);
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - titlelabel->getContentSize().height));
    //titlelabel->setTextColor(Color4B::ORANGE);
   /* titlelabel->enableOutline(Color4B::WHITE, 3);*/

    this->addChild(titlelabel, -1);

   
    //add main menu

    int index = 2;

    //startbutton
    auto new_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");    
    new_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
    new_button->setTitleText("NEW GAME");
   // new_button->setScale(0.8);
    new_button->setTitleFontName("craftacular/raw/font-export.fnt");
    new_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {

        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->replaceScene(GameScene::createScene());
            break;
        
        }
        });
   this->addChild(new_button);

   //options button
   auto options_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
   options_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
   options_button->setTitleText("OPTIONS");
   options_button->setTitleFontName("craftacular/raw/font-export.fnt");
   options_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {

       case ui::Widget::TouchEventType::ENDED:
           Director::getInstance()->replaceScene(OptionsScene::createScene());
           break;

       }
       });
   this->addChild(options_button);


   //controls button
   auto controls_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
   controls_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
   controls_button->setTitleText("CONTROLS");
   controls_button->setTitleFontName("craftacular/raw/font-export.fnt");
   controls_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {

       case ui::Widget::TouchEventType::ENDED:
           Director::getInstance()->replaceScene(ControlsScene::createScene());
           break;

       }
       });
   this->addChild(controls_button);


   //scoreboard button
   auto scoreboard_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
  scoreboard_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
  scoreboard_button->setTitleText("SCOREBOARD");
  scoreboard_button->setTitleFontName("craftacular/raw/font-export.fnt");
  scoreboard_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {

       case ui::Widget::TouchEventType::ENDED:
           Director::getInstance()->replaceScene(ScoreboardScene::createScene());
           break;

       }
       });
   this->addChild(scoreboard_button);

   //credits button
   auto credits_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
   credits_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
   credits_button->setTitleText("CREDITS");
   credits_button->setTitleFontName("craftacular/raw/font-export.fnt");
   credits_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {

       case ui::Widget::TouchEventType::ENDED:
           Director::getInstance()->replaceScene(CreditScene::createScene());
           break;

       }
       });
   this->addChild(credits_button);


   //quit button
   auto quit_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
   quit_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
   quit_button->setTitleText("QUIT");
   quit_button->setTitleFontName("craftacular/raw/font-export.fnt");
   quit_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {

       case ui::Widget::TouchEventType::ENDED:
           //Close the cocos2d-x game scene and quit the application
            Director::getInstance()->end();
           break;

       }
       });
   this->addChild(quit_button);

   //endgame button
   auto endgame_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
   endgame_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
   endgame_button->setTitleText("ENDGAME");
   endgame_button->setTitleFontName("craftacular/raw/font-export.fnt");
   endgame_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {

       case ui::Widget::TouchEventType::ENDED:
           Director::getInstance()->replaceScene(EndGameScene::createScene());
           break;

       }
       });
   this->addChild(endgame_button);


    /*_tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile("res/map.tmx");
    _tileMap->setAnchorPoint(Vec2(0, 0));
    _tileMap->setPosition(25, 20);*/


    //this->addChild(_tileMap);

    return true;
}


//void MainMenuScene::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();
//
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//
//
//}

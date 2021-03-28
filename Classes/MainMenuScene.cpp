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


USING_NS_CC;
using namespace cocos2d;
using namespace ui;

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
    auto titlelabel = Label::createWithTTF("TOMDICKHARRY","fonts/Marker Felt.ttf", 24);
    /*auto titlelabel = Label::create();
    titlelabel->setBMFontFilePath("craftacular/raw/font-title-export.fnt");
    titlelabel->setString("TOMDICKHARRY");*/
    //auto titlelabel = Label::createWithBMFont("craftacular/skin/font-title-export.fnt", "TOMDICKHARRY",);
    //titlelabel->setAnchorPoint(Vec2(0, 0));
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - visibleSize.width / 10));
    titlelabel->setTextColor(Color4B::ORANGE);
    titlelabel->enableOutline(Color4B::WHITE, 3);
    //Adds a child with the z-order of -2
    //scene->addChild(title_node, -2);
    this->addChild(titlelabel, -1);

    // create menu, it's an autorelease object
   /* menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/
    auto newgamebutton = Button::create();
    newgamebutton->setTitleText("NEW GAME");
    this->addChild(newgamebutton, 1);

    /*_tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile("res/map.tmx");
    _tileMap->setAnchorPoint(Vec2(0, 0));
    _tileMap->setPosition(25, 20);*/


    //this->addChild(_tileMap);

    return true;
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

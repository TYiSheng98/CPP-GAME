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

#include "OptionsScene.h"
#include "MainMenuScene.h"



USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;

Scene* OptionsScene::createScene()
{
    return OptionsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool OptionsScene::init()
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
    auto titlelabel = Label::createWithBMFont("craftacular/raw/font-title-export.fnt", "PREFERENCES");
    //titlelabel->setAnchorPoint(Vec2(0, 0));
    titlelabel->setBMFontSize(20);
    titlelabel->setColor(Color3B::YELLOW);
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - titlelabel->getContentSize().height));
    this->addChild(titlelabel, -1);

    //add main menu

    //auto mainmenu = Menu::create();
    int index = 3;

    //// startLabel
    //auto itemlabel = Label::createWithTTF("Back to menu", "fonts/Marker Felt.ttf", 24);
    //auto menuItem = MenuItemLabel::create(itemlabel);
    //menuItem->setCallback([&](cocos2d::Ref* sender) {
    //    Director::getInstance()->replaceScene(MainMenuScene::createScene());
    //    });
    //menuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2).x,
    //    (Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height).y - (++index) * 40));

    //mainmenu->addChild(menuItem, 2);
    //mainmenu->setPosition(Vec2::ZERO);

    //// CreditsLabel
    //itemlabel = Label::createWithTTF("Credits", "fonts/Marker Felt.ttf", 24);
    //menuItem = MenuItemLabel::create(itemlabel);
    //menuItem->setCallback([&](cocos2d::Ref* sender) {
    //    Director::getInstance()->replaceScene(CreditScene::createScene());
    //    });
    //menuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2).x,
    //    (Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height).y - (++index) * 40));

    //mainmenu->addChild(menuItem, 2);
    //mainmenu->setPosition(Vec2::ZERO);

    // add main menu
    //mainmenu->setPosition(Vec2::ZERO);
    //this->addChild(mainmenu, 1);

    //musicSLIDER
    auto music_slider = Slider::create("craftacular/raw/slider.9.png", "craftacular/raw/slider-knob.9.png");
    music_slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 60));
    music_slider->setMaxPercent(200);
    music_slider->setScale(0.8);
    music_slider->addEventListener(CC_CALLBACK_2(OptionsScene::sliderEvent, this));
    this->addChild(music_slider,2);

    //music toggle
    auto music_checkbox = CheckBox::create();
    music_checkbox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 60));
    //try button
    auto music_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    music_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 8));
    music_button->setTitleText("ON");
    music_button->setTitleFontName("craftacular/raw/font-export.fnt");
    music_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {

        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->replaceScene(MainMenuScene::createScene());
            break;

        }
        });
    this->addChild(music_button);


    // soundSLIDER
    auto sound_slider = Slider::create("craftacular/raw/slider.9.png", "craftacular/raw/slider-knob.9.png");
    sound_slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 60));
    sound_slider->setMaxPercent(200);
    sound_slider->setScale(0.8);
    sound_slider->addEventListener(CC_CALLBACK_2(OptionsScene::sliderEvent, this));
    this->addChild(sound_slider, 2);

    //sound toggle


    //menu button
    auto menu_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    menu_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/8));
    menu_button->setTitleText("MENU");
    menu_button->setTitleFontName("craftacular/raw/font-export.fnt");
    menu_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {

        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->replaceScene(MainMenuScene::createScene());
            break;

        }
        });
    this->addChild(menu_button);

    return true;
}



void OptionsScene::sliderEvent(Ref* sender, Slider::EventType type) {
    if (type == Slider::EventType::ON_SLIDEBALL_DOWN) {
                Slider* s = dynamic_cast<Slider*>(sender);
                int percent = s->getPercent();
                log("%d", percent);
          }
}

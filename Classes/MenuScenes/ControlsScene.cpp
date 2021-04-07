#include "ControlsScene.h"
#include "MainMenuScene.h"
#include <iostream>


USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

Scene* ControlsScene::createScene()
{
    return ControlsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ControlsScene::init()
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
    auto titlelabel = Label::createWithBMFont("craftacular/raw/font-title-export.fnt", "CONTROLS");
    titlelabel->setBMFontSize(20);
    titlelabel->setColor(Color3B::GREEN);
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.9));
    this->addChild(titlelabel, -1);


    string keyDetails[5] = { "MOVE UP:", "MOVE DOWN:", "MOVE LEFT:", "MOVE RIGHT:", "SHOOT:" };
    string keys[5] = { "ARROW UP", "ARROW DOWN", "ARROW LEFT", "ARROW RIGHT", "SPACEBAR" };
    int arrayElements = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < arrayElements; i++)
    {
        auto keyDetailsLabel = Label::createWithBMFont("craftacular/raw/font-export.fnt", keyDetails[i], TextHAlignment::CENTER);
        keyDetailsLabel->enableShadow();
        keyDetailsLabel->setColor(Color3B::YELLOW);
        keyDetailsLabel->enableBold();
        keyDetailsLabel->setIgnoreAnchorPointForPosition(true);
        keyDetailsLabel->setPosition(origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * (0.7 - (i * 0.1)));
        keyDetailsLabel->enableWrap(true);
        keyDetailsLabel->setOverflow(Label::Overflow::CLAMP);
        keyDetailsLabel->setDimensions(origin.x + visibleSize.width * 0.4, 0);
        keyDetailsLabel->setAlignment(TextHAlignment::CENTER);
        keyDetailsLabel->setBMFontSize(30);

        this->addChild(keyDetailsLabel);


        auto keysLabel = Label::createWithBMFont("craftacular/raw/font-export.fnt", keys[i], TextHAlignment::CENTER);
        keysLabel->enableShadow();
        keysLabel->setColor(Color3B::WHITE);
        keysLabel->enableBold();
        keysLabel->setIgnoreAnchorPointForPosition(true);
        keysLabel->setPosition(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * (0.7 - (i * 0.1)));
        keysLabel->enableWrap(true);
        keysLabel->setOverflow(Label::Overflow::CLAMP);
        keysLabel->setDimensions(origin.x + visibleSize.width * 0.4, 0);
        keysLabel->setAlignment(TextHAlignment::CENTER);
        keysLabel->setBMFontSize(30);

        this->addChild(keysLabel);

    }




    //Back button
    auto backButton = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    backButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10));
    backButton->setTitleText("RETURN TO MENU");
    backButton->setTitleFontName("craftacular/raw/font-export.fnt");
    backButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {

        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->replaceScene(MainMenuScene::createScene());
            break;

        }
        });
    this->addChild(backButton);


    return true;
}
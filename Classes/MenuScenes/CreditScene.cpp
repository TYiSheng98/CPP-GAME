#include "CreditScene.h"
#include "MainMenuScene.h"
#include <iostream>
#include "AudioEngine.h"

USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

Scene* CreditScene::createScene()
{
    return CreditScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameSceneScene.cpp\n");
}
class TeamMember {
private:
    string name;
    string role;
public:
    void setTeamMember(string, string);
    string getName();
    string getRole();
};

void TeamMember::setTeamMember(string name, string role) {
    this->name = name;
    this->role = role;
}
string TeamMember::getName() {
    return this->name;
}
string TeamMember::getRole() {
    return this->role;
}


// on "init" you need to initialize your instance
bool CreditScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    AudioEngine::preload("music/switch2.ogg");

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //background image
    auto bg = Sprite::create("img/dungeon_bg.jpg");
    float scale = MAX(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
    bg->setScale(scale);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bg, -2);

    //create title label
    auto titlelabel = Label::createWithBMFont("craftacular/raw/font-title-export.fnt", "CREDITS");
    titlelabel->setBMFontSize(20);
    titlelabel->setColor(Color3B::GREEN);
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.9));
    this->addChild(titlelabel, -1);

    //createdLabel
    auto createdLabel = Label::createWithBMFont("craftacular/raw/font-bold-export.fnt", "Created by Team 13");
    createdLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.75));
    createdLabel->setBMFontSize(30);
    /*createdLabel->enableShadow();
    createdLabel->enableBold();*/
    //createdLabel->enableOutline(Color4B::WHITE, 1);    
    //createdLabel->setTextColor(Color4B::RED);
    createdLabel->setColor(Color3B::RED);
    this->addChild(createdLabel, -1);
    
    //Add TeamMember into Array
    TeamMember member[6];
    member[0].setTeamMember("Heng JingZhi", "Team Lead & Gameplay");
    member[1].setTeamMember("Tay Chuen Ing Elger", "Level Design");
    member[2].setTeamMember("Sim Yi Jian", "Level Design");
    member[3].setTeamMember("Damien Teo En Hao", "Gameplay");
    member[4].setTeamMember("Tay Yi Sheng", "UI");
    member[5].setTeamMember("Chua Guang Jun", "UI");

    //Get Array Size
    int arrayElements = sizeof(member) / sizeof(member[0]);
    
    //Make a label for every name and role
    for (int i = 0; i < arrayElements; i++)
    {
        auto name = Label::createWithBMFont("craftacular/raw/font-export.fnt", member[i].getName());
        name->setBMFontSize(24);
        name->setPosition(Vec2(origin.x + visibleSize.width * 0.35, origin.y + (visibleSize.height * (0.65 - (i * 0.08)))));        
        name->setColor(Color3B::YELLOW);        
        this->addChild(name, -1);

        auto role = Label::createWithBMFont("craftacular/raw/font-export.fnt", member[i].getRole());        
        role->setBMFontSize(24);
        role->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + (visibleSize.height * (0.65 - (i * 0.08)))));
        role->setColor(Color3B::YELLOW);
        this->addChild(role, -1);

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
            AudioEngine::play2d("music/switch2.ogg", false, 1.0f);
            Director::getInstance()->replaceScene(MainMenuScene::createScene());
            break;

        }
        });
    this->addChild(backButton);


    return true;
}


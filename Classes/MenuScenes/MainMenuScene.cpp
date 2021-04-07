#include "MainMenuScene.h"
#include "OptionsScene.h"
#include "MainGameScene.h"
#include "ScoreboardScene.h"
#include "CreditScene.h"
#include "ControlsScene.h"
#include "EndGameScene.h"
#include "AudioEngine.h"




USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

static int bgm_id = -1;
static int sfx_id = -2;

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
    static bool first_installation = false;

    //read game settings from userdefault.xml in %appdata%/local
    int  mv = UserDefault::getInstance()->getIntegerForKey("music_volume");
    int  sv = UserDefault::getInstance()->getIntegerForKey("sound_volume");
    bool mt = UserDefault::getInstance()->getBoolForKey("music_toggle");
    bool st = UserDefault::getInstance()->getBoolForKey("sound_toggle");
    //bool first_time= UserDefault::getInstance()->getBoolForKey("first_install");

    FileUtils* fu = FileUtils::getInstance();

     //check for settings in player appdata dir
    UserDefault* userdefault = UserDefault::getInstance();
    string xml_path = UserDefault::getXMLFilePath();
    log("xml filepath: %s", xml_path.c_str());

    if (fu->isFileExist(xml_path) == 0) {
        log("UserDefault.xml do not exists!");

        log("writing default values to  UserDefault.xml in %localappdata% folder ....");
        userdefault->setIntegerForKey("music_volume", 50);
        userdefault->setIntegerForKey("sound_volume", 50);
        userdefault->setBoolForKey("music_toggle", 1);
        userdefault->setBoolForKey("sound_toggle", 1);
        first_installation = true;
    }
    else {
        log("UserDefault.xml  exists!");
        mv = UserDefault::getInstance()->getIntegerForKey("music_volume");
        sv = UserDefault::getInstance()->getIntegerForKey("sound_volume");
        mt = UserDefault::getInstance()->getBoolForKey("music_toggle");
        st = UserDefault::getInstance()->getBoolForKey("sound_toggle");

        if (mv == 0 && sv == 0 && mt == 0 && st == 0  && first_installation==0) {
            log("writing default values to  UserDefault.xml in local %appdata% folder ....");
            userdefault->setIntegerForKey("music_volume", 50);
            userdefault->setIntegerForKey("sound_volume", 50);
            userdefault->setBoolForKey("music_toggle", 1);
            userdefault->setBoolForKey("sound_toggle", 1);
            first_installation = true;
        }

    }


    AudioEngine::preload("music/switch2.ogg");
    AudioEngine::preload("music/Rolemusic_-_pl4y1ng.mp3");
    AudioEngine::setMaxAudioInstance(10);

    if (bgm_id != -1 || AudioEngine::getState(bgm_id) == AudioEngine::AudioState::PLAYING) {
        if (mt == 0) {
            AudioEngine::stop(bgm_id);
        }
        else if (AudioEngine::getState(bgm_id) != AudioEngine::AudioState::PLAYING) {
            bgm_id = AudioEngine::play2d("music/Rolemusic_-_pl4y1ng.mp3", true, float(mv / 100.0f));
        }
        else {
            AudioEngine::setVolume(bgm_id, float(mv / 100.0f));
        }

    }
    else if (bgm_id == -1 && AudioEngine::getState(bgm_id) != AudioEngine::AudioState::PLAYING && mt != false) {

        bgm_id = AudioEngine::play2d("music/Rolemusic_-_pl4y1ng.mp3", true, float(mv / 100.0f));
    }
    else if (first_installation == true && mt == 0) {
        bgm_id = AudioEngine::play2d("music/Rolemusic_-_pl4y1ng.mp3", true, float(50 / 100.0f));
    }
    else if (mt == false) {
        AudioEngine::stop(bgm_id);
    }

    st;
    if (first_installation == true && st == 0) {
        st = true;
        sv = 50;
    }
    else if (sfx_id != -2 && st == 0) {
        sv = 0;
    }
    else if (sfx_id != -2 || st == 1) {
        AudioEngine::setVolume(sfx_id, float(sv / 100.0f));

    }
    else if (sfx_id == -2 && st == 0) {
        sv = 0;
    }
    /*if (sfx_id != -2 || AudioEngine::getState(sfx_id) == AudioEngine::AudioState::PLAYING) {
        if (st == 0) {
            AudioEngine::stop(sfx_id);
        }
        else if (AudioEngine::getState(sfx_id) != AudioEngine::AudioState::PLAYING) {
            sfx_id = AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));
        }
        else {
            AudioEngine::setVolume(sfx_id, float(sv / 100.0f));
        }

    }
    else if (sfx_id == -2 && AudioEngine::getState(sfx_id) != AudioEngine::AudioState::PLAYING && st != false) {

        sfx_id = AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));
    }
    else if (st == false) {
        AudioEngine::stop(sfx_id);
    }*/



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
    titlelabel->setBMFontSize(34);
    titlelabel->setColor(Color3B::YELLOW);
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        visibleSize.height - visibleSize.height / 10));
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
            AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));
            AudioEngine::stop(bgm_id);
            Director::getInstance()->replaceScene(MainGameScene::createScene());
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
            AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));

            Scene* scene = OptionsScene::createScene(bgm_id, sfx_id);
            Director::getInstance()->replaceScene(scene);
            //Director::getInstance()->replaceScene(OptionsScene::createScene());
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
            AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));
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
            AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));
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
            AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));
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
            AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100.0f));
            AudioEngine::end();
            //Close the cocos2d-x game scene and quit the application
            Director::getInstance()->end();
            break;

        }
        });
    this->addChild(quit_button);

    /*
    //endgame button
    auto endgame_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    endgame_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (++index) * 70));
    endgame_button->setTitleText("ENDGAME");
    endgame_button->setTitleFontName("craftacular/raw/font-export.fnt");
    endgame_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {

        case ui::Widget::TouchEventType::ENDED:
            AudioEngine::play2d("music/switch2.ogg", false, float(sv/100.0f));
            Director::getInstance()->replaceScene(EndGameScene::createScene());
            break;

        }
        });
    //COMMENT THE CODE BELOW WHEN DEPLOYING. THIS ENDGAME BUTTON IS FOR DEBUGGING/TESTING ONLY
    this->addChild(endgame_button);
    */
    return true;
}

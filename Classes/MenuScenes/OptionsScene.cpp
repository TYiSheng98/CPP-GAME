#include "OptionsScene.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"


USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

static int bgm_id;
static int sfx_id;

int mv; int sv;
bool mt; bool st;

Scene* OptionsScene::createScene(int bgm,int sfx)
{
    bgm_id = bgm;
    log("%d", bgm_id);
    /*AudioEngine::getState(bgm_id);
    AudioEngine::getProfile(bgm_id);
    AudioEngine::getVolume(bgm_id);*/

    sfx_id = sfx;
    log("%d", sfx_id);


    return OptionsScene::create();
}
Scene* OptionsScene::createScene()
{
    /*bg_music = bg_music_id;
    log("%s", bg_music);*/
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


    UserDefault* userdefault = UserDefault::getInstance();
    mv = UserDefault::getInstance()->getIntegerForKey("music_volume");
     sv = UserDefault::getInstance()->getIntegerForKey("sound_volume");
     mt = UserDefault::getInstance()->getBoolForKey("music_toggle");
     st = UserDefault::getInstance()->getBoolForKey("sound_toggle");
    log("mv: %d", mv);
log("sv: %d", sv);
log("mt: %d", mt);
log("st: %d", st);
  /*  AudioEngine::preload("music/switch2.ogg");*/

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //background image
    auto bg = Sprite::create("img/dungeon_bg.jpg");
    float scale = MAX(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
    bg->setScale(scale);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bg, -2);

    //create title label
    auto titlelabel = Label::createWithBMFont("craftacular/raw/font-title-export.fnt", "OPTIONS");
    //titlelabel->setAnchorPoint(Vec2(0, 0));
    titlelabel->setBMFontSize(20);
    titlelabel->setColor(Color3B::GREEN);
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - titlelabel->getContentSize().height));
    this->addChild(titlelabel, -1);


    int index = 1;
    const int padding = 100;
    string label_name_array[4] = { "music_v_label", "music_slider_label", "sound_v_label", "sound_slider_label" };
    string label_array[4] = { "MUSIC VOLUME", "MUSIC", "SOUND VOLUME", "SOUND" };
    int arrsize = sizeof(label_array) / sizeof(label_array[0]);
    for (int i = 0; i < arrsize; i++)
    {
        auto name = Label::createWithBMFont("craftacular/raw/font-bold-export.fnt", label_array[i]);
        name->setBMFontSize(32);
        name->setName(label_name_array[i]);
        name->setPosition(Vec2(origin.x + visibleSize.width * 0.3, visibleSize.height - (++index) * padding));
        name->setColor(Color3B::WHITE);
        this->addChild(name, -1);

    }




    index = 1;
    //musicSLIDER
    auto music_slider = Slider::create("craftacular/raw/slider.9.png", "craftacular/raw/slider-knob.9.png");
    music_slider->setPosition(Vec2(origin.x + visibleSize.width * 0.7, visibleSize.height - (++index) * padding));
    music_slider->setPercent(mv);
    music_slider->setName("music_slider");
    music_slider->addTouchEventListener(CC_CALLBACK_2(OptionsScene::sliderEvent, this));
    this->addChild(music_slider, 2);



    //music toggle button
    auto music_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    music_button->setPosition(Vec2(origin.x + visibleSize.width * 0.7, visibleSize.height - (++index) * padding));
    if (mt == 0) {
        music_button->setTitleText("OFF");
    }
    else {
        music_button->setTitleText("ON");
    }    
    music_button->setName("music_button");
    music_button->setTitleFontName("craftacular/raw/font-export.fnt");
    music_button->setName("music_button");
    music_button->addTouchEventListener(CC_CALLBACK_2(OptionsScene::btnpressed, this));

    this->addChild(music_button);


    // soundSLIDER
    auto sound_slider = Slider::create("craftacular/raw/slider.9.png", "craftacular/raw/slider-knob.9.png");
    sound_slider->setPosition(Vec2(origin.x + visibleSize.width * 0.7, visibleSize.height - (++index) * padding));
    sound_slider->setName("sound_slider");
    sound_slider->setPercent(sv);
    sound_slider->addTouchEventListener(CC_CALLBACK_2(OptionsScene::sliderEvent, this));
    this->addChild(sound_slider, 2);

    //sound toggle button
    auto sound_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    sound_button->setPosition(Vec2(origin.x + visibleSize.width * 0.7, visibleSize.height - (++index) * padding));
    sound_button->setName("sound_button");
    if (st == false) {
        sound_button->setTitleText("OFF");
    }
    else {
        sound_button->setTitleText("ON");
    }
    sound_button->setTitleFontName("craftacular/raw/font-export.fnt");
    sound_button->addTouchEventListener(CC_CALLBACK_2(OptionsScene::btnpressed, this));

    this->addChild(sound_button);

    //menu button
    auto menu_button = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    menu_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 8));
    menu_button->setTitleText("APPLY");
    menu_button->setTitleFontName("craftacular/raw/font-export.fnt");
    menu_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {

        case ui::Widget::TouchEventType::ENDED:
            AudioEngine::play2d("music/switch2.ogg", false, float(sv/100));
            Director::getInstance()->replaceScene(MainMenuScene::createScene());
            break;

        }
        });
    this->addChild(menu_button);

    return true;
}



void OptionsScene::sliderEvent(Ref* sender, Slider::TouchEventType type) {
    AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100));
    if (type == Slider::TouchEventType::ENDED) {
        
        UserDefault* userdefault = UserDefault::getInstance();
        Slider* s = dynamic_cast<Slider*>(sender);
        int percent = s->getPercent();
        string name = s->getName();
        log("%s :%d", name.c_str(), percent);
        if (name == "music_slider") {
            userdefault->setIntegerForKey("music_volume", percent);
           
        }
        else if (name == "sound_slider") {
            userdefault->setIntegerForKey("sound_volume", percent);

        }
    }
}
void OptionsScene::btnpressed(Ref* sender, Button::TouchEventType type)
{
    UserDefault* userdefault = UserDefault::getInstance();
    AudioEngine::play2d("music/switch2.ogg", false, float(sv / 100));
    if (type == Button::TouchEventType::ENDED) {
        /*AudioEngine::play2d("music/switch2.ogg", false, float(sv/100));*/
        Button* a = dynamic_cast<Button*>(sender);
        string name = a->getName();
        string toggle_value = a->getTitleText();

        if (toggle_value == "ON") {
            a->setTitleText("OFF");
            toggle_value = a->getTitleText();
            log("%s value: %s", name.c_str(), toggle_value.c_str());
            if (name == "music_button") {
                userdefault->setBoolForKey("music_toggle", 0);
            }
            else if (name == "sound_button") {
                userdefault->setBoolForKey("sound_toggle", 0);
            }
        }
        else {
            a->setTitleText("ON");
            toggle_value = a->getTitleText();
            log("%s value: %s", name.c_str(), toggle_value.c_str());
            if (name == "music_button") {
                userdefault->setBoolForKey("music_toggle", 1);
            }
            else if (name == "sound_button") {
                userdefault->setBoolForKey("sound_toggle", 1);
            }
        }

    }
}
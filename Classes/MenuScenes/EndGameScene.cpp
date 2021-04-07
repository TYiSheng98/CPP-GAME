#include "EndGameScene.h"
#include "MainMenuScene.h"
#include <string>
#include "AudioEngine.h"


USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

static string input_name = "";
static int score = 100;
Scene* EndGameScene::createScene()
{
    return EndGameScene::create();
}

Scene* EndGameScene::createScene(int game_score)
{
    score = game_score;
    log("%d", score);
   
    return EndGameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameSceneScene.cpp\n");
}


// on "init" you need to initialize your instance
bool EndGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    AudioEngine::preload("music/switch2.ogg");
    AudioEngine::preload("music/game-over-arcade.mp3");
    AudioEngine::play2d("music/game-over-arcade.mp3", false, float(1));

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //background image
    auto bg = Sprite::create("img/dungeon_bg.jpg");
    float scale = MAX(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
    bg->setScale(scale);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bg, -2);

    //create title label
    auto titlelabel = Label::createWithBMFont("craftacular/raw/font-title-export.fnt", "GAME OVER");
    //titlelabel->setAnchorPoint(Vec2(0, 0));
    titlelabel->setBMFontSize(30);
    titlelabel->setColor(Color3B::RED);
    titlelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - titlelabel->getContentSize().height));
    this->addChild(titlelabel, -1);
   
    
    int i = 0;

    auto score_label = Label::createWithBMFont("craftacular/raw/font-bold-export.fnt", "SCORE");
    score_label->setBMFontSize(50);
    score_label->setName("score_label");
    score_label->setColor(Color3B::YELLOW);
    score_label->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.65 - (i * 0.08)))));
    this->addChild(score_label, -1);
    

    auto scoring_label = Label::createWithBMFont("craftacular/raw/font-bold-export.fnt", to_string(score));
    scoring_label->setBMFontSize(50);
    scoring_label->setName("scoring_label");
    scoring_label->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.65 - (++i * 0.08)))));
    this->addChild(scoring_label, -1);
 
    auto textField = TextField::create("Player (MAX 10 CHARACTERS)", "craftacular/raw/font-export.fnt", 25);  
    textField->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.65 - (++i * 0.08)))));
    textField->setFontName("craftacular/raw/font-bold-export.fnt");
    textField->setInsertText(1);
    textField->setString("P1");
    textField->setMaxLengthEnabled(1);
    textField->setMaxLength(10);
    textField->setTextColor(Color4B::ORANGE);
    textField->setName("player_name");
    textField->setName("player_name");
    textField->addEventListener(CC_CALLBACK_2(EndGameScene::txtfieldevent, this));
 /*  textField->addEventListener([&](Ref* sender, TextField::EventType type) {
        TextField* tf = dynamic_cast<TextField*>(sender);
        switch (type)
        {

        case TextField::EventType::INSERT_TEXT:
            p1.setName(tf->getString());
            
            log("%s", p1.getName());
            break;

        }
    });*/
    this->addChild(textField,-1);

    

    //Save button
    auto saveButton = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    saveButton-> setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.65 - (++i * 0.08)))));
    saveButton->setTitleText("SAVE");
    saveButton->setTitleFontName("craftacular/raw/font-export.fnt");
    saveButton->addTouchEventListener(CC_CALLBACK_2(EndGameScene::savepressed, this));
    //saveButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
    //    switch (type)
    //    {

    //    case ui::Widget::TouchEventType::ENDED:
    //        //Player p1;
    //        //score;
    //        //log("%d", score);
    //        //p1.setPLAYER(player_n, stoi(scoring_label->getString()));
    //        //textField->setEnabled(0);
    //        //textField->getString();
    //        
    //        //log("%s :%s", scoring_label->getString(), textField->getUserData());
    //        break;

    //    }
    //    });
    this->addChild(saveButton,-1);


    //Back button
    auto backButton = Button::create("craftacular/raw/button.9.png", "craftacular/raw/button-hover.9.png", "craftacular/raw/button-disabled.9.png");
    backButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
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

void EndGameScene::txtfieldevent(Ref* sender, TextField::EventType type) {
    TextField * tf = dynamic_cast<TextField*>(sender);
    
    switch (type) {
    case  TextField::EventType::INSERT_TEXT:
        input_name =tf->getString();
        log("%s", input_name.c_str());

    case TextField::EventType::DELETE_BACKWARD:
        input_name = tf->getString();
        log("%s", input_name.c_str());
    }
}

void EndGameScene::savepressed(Ref* sender, Button::TouchEventType type)
{

    if (type == Button::TouchEventType::ENDED) {
        AudioEngine::play2d("music/switch2.ogg", false, 1.0f);
        Button* a = dynamic_cast<Button*>(sender);
        string name = a->getName();
        string b = a->getTitleText();

        log("SAVE BUTTON CLICKED");
        a->setTitleText("SAVED");
        a->setTouchEnabled(0);
        a->setBright(false);
        log("%s:%d", input_name.c_str(),score);

        FileUtils*fu = FileUtils::getInstance();
  
        fu->setWritablePath("Resources\\leaderboard\\");
        string default_res_path= fu ->getDefaultResourceRootPath()+"leaderboard\/";
        //save score to scoreboard.txt
        string score_file = default_res_path + "score.txt";
        /*FileUtils* fu = FileUtils::getInstance();*/
        if (fu->isFileExist(default_res_path+"score.txt") == 0) {
            //CREATE FILE
            fu->writeStringToFile("P1,0\n", score_file);
          /*  Data d;
            fu->writeDataToFile(d, score_file);*/
;            log("scoreboard.txt created!");
        }
        else {
            //append data to file
            string str_buf = fu->getStringFromFile(score_file);
            fu->writeStringToFile(str_buf+input_name+","+to_string(score)+"\n", score_file);
            log("scoreboard.txt appended!");
        }

    }
}
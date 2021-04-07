#include "ScoreboardScene.h"
#include "MainMenuScene.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;


Scene* ScoreboardScene::createScene()
{
    return ScoreboardScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameSceneScene.cpp\n");
}
struct Leaderboard
{
    string name;
    string score;

};
bool compareByScore(const Leaderboard& a, const Leaderboard& b)
{
    return stoi(a.score) > stoi(b.score);
}
// on "init" you need to initialize your instance
bool ScoreboardScene::init()
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
    auto titlelabel = Label::createWithBMFont("craftacular/raw/font-title-export.fnt", "LEADERBOARD");
    titlelabel->setBMFontSize(20);
    titlelabel->setColor(Color3B::ORANGE);
    titlelabel->setPosition((Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.9)));
    this->addChild(titlelabel, -1);

    Size scollFrameSize = Size(600, 450);
    auto containerSize = Size(scollFrameSize.width, scollFrameSize.height * 2);
    auto leaderView = ScrollView::create();
    leaderView->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
    leaderView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    leaderView->setContentSize(scollFrameSize);
    leaderView->setInnerContainerSize(containerSize);
    leaderView->setBackGroundColor(Color3B::GRAY);
    leaderView->setBackGroundColorType(ui::Layout::BackGroundColorType::GRADIENT);
    leaderView->setBackGroundColorOpacity(50);
    leaderView->setDirection(ScrollView::Direction::VERTICAL);
    leaderView->setBounceEnabled(true);
    leaderView->setTouchEnabled(true);
    leaderView->setScrollBarEnabled(true);
    leaderView->setInertiaScrollEnabled(true);
    this->addChild(leaderView, -1);




    //Read score.txt
    FileUtils* fu = FileUtils::getInstance();
    auto contents = fu->getStringFromFile("leaderboard\\score.txt");
    vector<Leaderboard> vleaderboard;
    if (!contents.empty()) {
        try {
            istringstream file(contents);
            while (getline(file, contents))
            {
                istringstream iss(contents);
                Leaderboard lead;
                getline(iss, lead.name, ',');
                getline(iss, lead.score);
                vleaderboard.push_back(lead);
            }
        }
        catch (std::exception const& e) {
            cout << "There was an error: " << e.what() << endl;
        }
    }
    else {
        cocos2d::log("File doesn't exist");
    }

    string details[3] = { "RANK", "NAME", "SCORE" };
    int arrayElements = sizeof(details) / sizeof(details[0]);

    for (int i = 0; i < arrayElements; i++)
    {

        //auto detailsLabel = Label::createWithTTF(details[i], "fonts/Marker Felt.ttf", 30);
        auto detailsLabel = Label::createWithBMFont("craftacular/raw/font-bold-export.fnt", details[i], TextHAlignment::CENTER);
        detailsLabel->setBMFontSize(30);
        detailsLabel->setColor(Color3B::RED);
        detailsLabel->enableShadow();
        detailsLabel->enableBold();
        //detailsLabel->enableOutline(Color4B::WHITE, 1);
        //detailsLabel->setTextColor(Color4B::RED);
        detailsLabel->setIgnoreAnchorPointForPosition(true);
        detailsLabel->setPosition(containerSize.width * (0.05 + (i * 0.3)), containerSize.height * 0.95);
        detailsLabel->enableWrap(true);
        detailsLabel->setDimensions(containerSize.width * 0.25, 0);
        detailsLabel->setAlignment(TextHAlignment::CENTER);
        detailsLabel->setOverflow(Label::Overflow::CLAMP);

        leaderView->addChild(detailsLabel);
    }

    std::sort(vleaderboard.begin(), vleaderboard.end(), compareByScore);
    for (int i = 0; i < vleaderboard.size(); ++i)
    {

        Leaderboard& lead = vleaderboard[i];
        string rank = to_string(i + 1);
        //rankLabel
        //auto rankLabel = Label::createWithTTF(rank, "fonts/Marker Felt.ttf", 30);
        auto rankLabel = Label::createWithBMFont("craftacular/raw/font-export.fnt", rank, TextHAlignment::CENTER);
        rankLabel->enableShadow();
        rankLabel->setColor(Color3B::MAGENTA);
        rankLabel->enableBold();
        /*rankLabel->enableOutline(Color4B::WHITE, 1);
        rankLabel->setTextColor(Color4B::MAGENTA);*/
        rankLabel->setIgnoreAnchorPointForPosition(true);
        rankLabel->setPosition(containerSize.width * 0.05, containerSize.height * (0.9 - (i * 0.05)));
        rankLabel->enableWrap(true);
        rankLabel->setOverflow(Label::Overflow::CLAMP);
        rankLabel->setDimensions(containerSize.width * 0.25, 0);
        rankLabel->setAlignment(TextHAlignment::CENTER);
        rankLabel->setBMFontSize(30);

        leaderView->addChild(rankLabel);


        //nameLabel
        auto nameLabel = Label::createWithBMFont("craftacular/raw/font-export.fnt", lead.name, TextHAlignment::CENTER);
        nameLabel->enableShadow();
        nameLabel->enableBold();
        nameLabel->setColor(Color3B::MAGENTA);
        /*nameLabel->enableOutline(Color4B::WHITE, 1);
        nameLabel->setTextColor(Color4B::MAGENTA);*/
        nameLabel->setIgnoreAnchorPointForPosition(true);
        nameLabel->setPosition(containerSize.width * 0.35, containerSize.height * (0.9 - (i * 0.05)));
        nameLabel->enableWrap(true);
        nameLabel->setOverflow(Label::Overflow::CLAMP);
        nameLabel->setDimensions(containerSize.width * 0.25, 0);
        nameLabel->setAlignment(TextHAlignment::CENTER);
        nameLabel->setBMFontSize(24);

        leaderView->addChild(nameLabel);

        //scoreLabel
        auto scoreLabel = Label::createWithBMFont("craftacular/raw/font-export.fnt", lead.score, TextHAlignment::CENTER);
        scoreLabel->enableShadow();
        scoreLabel->enableBold();
        scoreLabel->setColor(Color3B::MAGENTA);
        /*scoreLabel->enableOutline(Color4B::WHITE, 1);
        scoreLabel->setTextColor(Color4B::MAGENTA);*/
        scoreLabel->setIgnoreAnchorPointForPosition(true);
        scoreLabel->setPosition(containerSize.width * 0.65, containerSize.height * (0.9 - (i * 0.05)));
        scoreLabel->enableWrap(true);
        scoreLabel->setOverflow(Label::Overflow::CLAMP);
        scoreLabel->setDimensions(containerSize.width * 0.25, 0);
        scoreLabel->setAlignment(TextHAlignment::CENTER);
        scoreLabel->setBMFontSize(30);

        leaderView->addChild(scoreLabel);
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
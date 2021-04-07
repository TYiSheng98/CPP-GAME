#include "MainGameScene.h"
#include "MenuScenes/EndGameScene.h"
#include "Characters/Hero.h"
#include "Characters/Mob.h"
#include "Control.h"
#include "AudioEngine.h"
#include "level_logic.h"
#include <chrono>
#include <ctime>

USING_NS_CC;
using namespace cocos2d;

static int bgm_id;
Scene* MainGameScene::createScene()
{
    return MainGameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    //add ingame music
    int  mv = UserDefault::getInstance()->getIntegerForKey("music_volume");
    bool mt = UserDefault::getInstance()->getBoolForKey("music_toggle");


    AudioEngine::preload("music/maple-bgm.mp3");
    if (mt == true) {
        bgm_id = AudioEngine::play2d("music/maple-bgm.mp3", true, float(mv / 100.0f));
    }

    initializeObjects();

    return true;
}


void MainGameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

// return the controller for the character
const Control& MainGameScene::getController() const
{
    return controls;
}

// make a 2D rectangle defined by x, y position and width, height
cocos2d::Rect MainGameScene::getGameArea() const
{
    auto rect = _tileMap->getBoundingBox();

    rect.size.width -= 2 * _tileMap->getTileSize().width;
    rect.size.height -= 2 * _tileMap->getTileSize().height;

    rect.origin += _tileMap->getTileSize();

    return rect;
}

// gets a vector of pointers for vectors of movable objects 
std::vector<std::shared_ptr<Movable>>& MainGameScene::getGameObjects()
{
    return gameObjects;
}

// add movable object into the vector
void MainGameScene::instantiateGameObject(const std::shared_ptr<Movable>& gameObject)
{
    gameObjectsToAdd.push_back(gameObject);
}

// send movable object into a vector to be cleared
void MainGameScene::destroyGameObject(Movable* gameObject)
{
    gameObjectsToDelete.push_back(gameObject);
}

// return the hero
Hero* MainGameScene::getHero()
{
    return hero.get();
}


// this function will initialize the required objects
void MainGameScene::initializeObjects() {
    _tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile("res/map.tmx");
    _tileMap->setAnchorPoint(Vec2(0, 0));
    _tileMap->setPosition(25, 20);

    // x, y, file_path, size, char_type, maxSpeed, hp
    hero = std::make_shared<Hero>(500, 400, "char/hero.png", 5.0f, "hero", 100.0f, 3.0f);

    this->initializeHUD();
    this->addChild(_tileMap);
    this->addChild(hero->get_sprite());

    // spawn mobs
    levels = new level_logic(current_level);
    levels->initialize_level(this);
    start_time = std::chrono::system_clock::now();

    // sets the event dispatcher to catch for events from this layer
    _eventDispatcher->addEventListenerWithSceneGraphPriority(controls.get_kb_listener(), this);

    // let the MainGameScene know that there will be updates.
    this->scheduleUpdate();
}

void MainGameScene::initializeHUD() {

    // create a layer for HUD items
    HUD = cocos2d::Layer::create();
    scorePoints = Label::createWithBMFont("craftacular/raw/font-bold-export.fnt", "a");
    scorePoints->setScale(0.75);
    scorePoints->setPosition(Vec2(hero->getPosition().x, hero->getPosition().y + 140));
    HUD->addChild(scorePoints);

    currentLevel = Label::createWithBMFont("craftacular/raw/font-bold-export.fnt", "a");
    currentLevel->setScale(0.3);
    currentLevel->setPosition(Vec2(hero->getPosition().x + 160, hero->getPosition().y + 140));
    HUD->addChild(currentLevel);

    // camera to follow character, is updated in the update function
    cam = this->getDefaultCamera();
    cam->setPosition3D(Vec3(hero->getPosition().x, hero->getPosition().y, 300));

    // put the heart sprites into the container
    for (int i = 0; i < hero->getHealth(); i++) {
        containerOfHealth.push_back(cocos2d::Sprite::create("craftacular/raw/heart.png"));
    }

    // fill container with position for the health sprites
    for (cocos2d::Sprite* a_Sprite : containerOfHealth) {
        a_Sprite->setPosition(hero->getPosition().x - 200, hero->getPosition().y + 150);
        HUD->addChild(a_Sprite);
    }

    // bring to front
    this->addChild(HUD, 1);
}

void MainGameScene::updateHUD() {
    // to update the camera to follow the hero
    cam->setPosition(Vec2(hero->getPosition().x, hero->getPosition().y));

    // to update the score to be in the right place and the correct score
    scorePoints->setString(std::to_string(player_score));
    scorePoints->setPosition(Vec2(hero->getPosition().x, hero->getPosition().y - 150));

    // to update the current level
    currentLevel->setString("Current Level : " + std::to_string(current_level));
    currentLevel->setPosition(Vec2(hero->getPosition().x + 160, hero->getPosition().y + 150));

    // checks if the current container size is synced with the hero health
    // else remove from back
    if (containerOfHealth.size() != (int)hero->getHealth()) {
        auto behind_sprite = containerOfHealth.back();
        HUD->removeChild(behind_sprite);
        containerOfHealth.pop_back();
    }

    // to update the hearts to follow the camera
    int i = 0;
    for (std::vector<cocos2d::Sprite*>::iterator it = containerOfHealth.begin(); it != containerOfHealth.end(); it++) {
        (**it).setPosition(hero->getPosition().x - 200 + i * 16, hero->getPosition().y + 150);
        i++;
    }
}

// used in Character.cpp to add score if != "hero"
void MainGameScene::add_score() {
    player_score += 100;
}

int MainGameScene::get_current_level() {
    return current_level;
}


// this function acts as the main update loop for the game
// overrides inbuilt update function
void MainGameScene::update(float delta) {

    // for each movable object that needs to be added, add the sprite to the scene
    for (const auto& toAdd : gameObjectsToAdd)
    {
        gameObjects.push_back(toAdd);
        addChild(toAdd->get_sprite());
    }
    gameObjectsToAdd.clear();

    hero->update(this, delta);

    // for each movable object in the game, update their movements
    for (auto& gameObject : gameObjects)
    {
        gameObject->update(this, delta);
    }

    // for each object in the vector to be deleted, removeChild from scene and erase.
    for (const auto& toDelete : gameObjectsToDelete)
    {
        for (auto it = gameObjects.begin(); it != gameObjects.end(); )
        {
            if (it->get() == toDelete)
            {
                removeChild(toDelete->get_sprite());
                it = gameObjects.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
    gameObjectsToDelete.clear();

    //Upon hero death, show endgame
    if (*hero < 0.0f)
    {
        AudioEngine::stop(bgm_id);
        AudioEngine::end();

        Scene* scene = EndGameScene::createScene(player_score);
        Director::getInstance()->replaceScene(scene);
    }

    updateHUD();
    controls.update();

    current_time = std::chrono::system_clock::now();

    // every 30 seconds, increase level and spawn next wave
    // try to check for the elapsed time, if more than 30s then throw exception n catch to update level
    try {
        auto elapsed_time = current_time - start_time;
        if (elapsed_time > std::chrono::seconds(30))
            throw(elapsed_time);
    }
    catch (std::chrono::duration<__int64, std::ratio<1, 10000000>>) {
        cocos2d::log("30s have passed");

        current_level++;
        levels->update_level(current_level);
        // spawn the next wave
        levels->initialize_level(this);

        // reset counter
        start_time = current_time;
    }


}
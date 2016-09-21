#include "MainMenuScene.h"
#include "GameScene.h"
#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "GameSystem.h"
#include "SaveScene.h"
#include "LoadScene.h"

USING_NS_CC;

#define RAIN_MAX 130
#define RAIN_LEN_MAX 30
#define RAIN_LEN_MIN 1
#define RAIN_SPEED 2500
#define RAIN_OVER_RADIS 50
#define RAIN_RANGE 100

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
    if (rains.size() > 0){
        for (Rain* rain : rains){
            delete(rain);
            rain = nullptr;
        }
        rains.clear();
    }
    if (rainOvers.size() > 0){
        for (RainOver* ro : rainOvers){
            delete(ro);
            ro = nullptr;
        }
    }
    rainOvers.clear();
}

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//初始化系统信息
	////GameSystem::getInstance();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//设定背景层
	auto backgroundLayer = LayerColor::create(Color4B::WHITE);
	auto backgroundjpg = Sprite::create("ui/Title/bg2_title.jpg");
    backgroundjpg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	backgroundjpg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y));
	backgroundLayer->addChild(backgroundjpg, 0);

	//logo
    auto lastdayLogo = Sprite::create("ui/Title/bg_title_logo.png");
    lastdayLogo->setPosition(250,100);
    
    //绘制下雨效果
    drawNode = DrawNode::create();
    addChild(drawNode, 5);
    
    backgroundLayer->addChild(lastdayLogo);

    scheduleUpdate();
    
    appendRain();
    
	//菜单按钮
	auto buttonNew = MenuItemImage::create("ui/Title/btn_title_new_normal.png", "ui/Title/btn_title_new_touch.png", CC_CALLBACK_0(MainMenu::newgame, this));
	buttonNew->setPosition(Vec2(850, 400));

	auto buttonLoad = MenuItemImage::create("ui/Title/btn_title_load_normal.png", "ui/Title/btn_title_load_touch.png", CC_CALLBACK_0(MainMenu::load, this));
	buttonLoad->setPosition(Vec2(850, 300));

	auto buttonConfig = MenuItemImage::create("ui/Title/btn_title_config_normal.png", "ui/Title/btn_title_config_touch.png",CC_CALLBACK_0(MainMenu::config, this));
	buttonConfig->setPosition(Vec2(850, 200));

	//auto buttonExit = MenuItemImage::create("ui/Title/button_exit.png", "ui/Title/button_exit_down.png",CC_CALLBACK_1(MainMenu::menuExit, this));
	//buttonExit->setPosition(Vec2(900, visibleSize.height - 443));

	auto menu = Menu::create(buttonNew, buttonLoad, buttonConfig, NULL);
	menu->setPosition(Vec2::ZERO);



	

	backgroundLayer->addChild(menu, 4);
	this->addChild(backgroundLayer, 0);

	return true;

}

void MainMenu::test()
{
	log("Bingo!");
}

void MainMenu::menuExit(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenu::newgame()
{
	GameSystem::getInstance()->setGameScene(GameScene::createScene());
	auto scene = GameSystem::getInstance()->getGameScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenu::config()
{
	//直接将要显示的Scene  push.而不是push当前的runningScene...
	Director::getInstance()->pushScene(SettingScene::createScene());
}

void MainMenu::load()
{
	Director::getInstance()->pushScene(LoadScene::createScene());
}

void MainMenu::update(float dt){
    drawNode->clear();
    appendRain();
    
    for (auto i = rainOvers.begin(); i != rainOvers.end();){
        auto o = *i;
        drawNode->drawCircle(Vec2(o->x, o->y), o->r, 360, 100, false, 1.f, 0.4f, Color4F(1, 1, 1, o->alpha));
        o->r += (RAIN_LEN_MAX - o->y) / RAIN_LEN_MAX *RAIN_OVER_RADIS* dt;
        o->alpha -= dt;
        if (o->alpha <= 0){
            i = rainOvers.erase(i);
            delete(o);
        }
        else{
            i++;
        }
    }
    
    for (auto i = rains.begin(); i != rains.end();){
        auto r = *i;
        drawNode->drawLine(Vec2(r->x, r->y), Vec2(r->x, r->y + r->len), Color4F(1, 1, 1, r->alpha*0.5f));
        float s = RAIN_SPEED * dt;
        if (r->y > (RAIN_LEN_MAX - r->len) / RAIN_LEN_MAX*RAIN_RANGE){
            r->y -= (r->landLen / RAIN_LEN_MAX) * s;
            i++;
        }
        else if (!r->isLand){
            i++;
            r->isLand = true;
            
            auto over = new RainOver();
            over->x = r->x;
            over->y = r->y;
            over->alpha = r->len / RAIN_LEN_MAX*0.5f+0.3f;
            over->r = 0;
            rainOvers.push_back(over);
        }
        else{
            r->len -= (r->landLen / RAIN_LEN_MAX) * s;
            if (r->len <= 0){
                i = rains.erase(i);
                delete(r);
            }
            else{
                i++;
            }
        }
    }
    
}

void MainMenu::appendRain()
{
    while (rains.size() < RAIN_MAX){
        auto r = new Rain();
        r->x = rand_0_1()*getContentSize().width;
        r->y = getContentSize().height + RAIN_LEN_MAX;
        r->len = rand_0_1() * (RAIN_LEN_MAX - RAIN_LEN_MIN) + RAIN_LEN_MIN;
        r->landLen = r->len;
        r->alpha = (r->len - RAIN_LEN_MIN) / (RAIN_LEN_MAX - RAIN_LEN_MIN);
        r->isLand = false;
        rains.push_back(r);
    }
}
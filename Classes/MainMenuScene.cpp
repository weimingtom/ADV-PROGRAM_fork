#include "MainMenuScene.h"
#include "GameScene.h"
#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "GameSystem.h"
#include "SaveScene.h"
#include "LoadScene.h"

USING_NS_CC;

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
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
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	auto backgroundjpg = Sprite::create("ui/Title/50mRoadRain.jpg");
	backgroundjpg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundLayer->addChild(backgroundjpg, 0);

	//logo
    
    auto lastdayLogo = Sprite::create("ui/Title/title.png");
    lastdayLogo->setPosition(700,522);
    backgroundLayer->addChild(lastdayLogo);

	//菜单按钮
	auto buttonNew = MenuItemImage::create("ui/Title/mainNewNormal.png", "ui/Title/mainNewTouch.png", CC_CALLBACK_0(MainMenu::newgame, this));
	buttonNew->setPosition(Vec2(800, 350));

	auto buttonLoad = MenuItemImage::create("ui/Title/mainLoadNormal.png", "ui/Title/mainLoadTouch.png", CC_CALLBACK_0(MainMenu::load, this));
	buttonLoad->setPosition(Vec2(800, 250));

	auto buttonConfig = MenuItemImage::create("ui/Title/mainConfigNormal.png", "ui/Title/mainConfigTouch.png",CC_CALLBACK_0(MainMenu::config, this));
	buttonConfig->setPosition(Vec2(800, 150));

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
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(SettingScene::createScene());
}

void MainMenu::load()
{
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(LoadScene::createScene());
}
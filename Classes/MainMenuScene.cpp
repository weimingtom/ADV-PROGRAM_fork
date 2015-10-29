#include "MainMenuScene.h"
#include "GameScene.h"
#include "SettingScene.h"

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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//设定背景层
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	auto backgroundEffect1 = Sprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	auto backgroundEffect2 = Sprite::create("/ui/backgroundEffect/fullscreen_smoke_2.png");
	backgroundEffect1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundEffect2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//logo
	auto gameTitle = Sprite::create("/ui/game_title.png");
	gameTitle->setPosition(Vec2(433, 358));

	//菜单按钮
	auto buttonNew = MenuItemImage::create("/ui/Title/button_new.png", "/ui/Title/button_new_down.png", CC_CALLBACK_0(MainMenu::newgame, this));
	buttonNew->setPosition(Vec2(1114, visibleSize.height - 243));

	auto buttonLoad = MenuItemImage::create("/ui/Title/button_load.png","/ui/Title/button_load_down.png");
	buttonLoad->setPosition(Vec2(1114, visibleSize.height - 293));

	auto buttonCG = MenuItemImage::create("/ui/Title/button_cg.png", "/ui/Title/button_cg_down.png");
	buttonCG->setPosition(Vec2(1114, visibleSize.height - 343));

	auto buttonConfig = MenuItemImage::create("/ui/Title/button_config.png", "/ui/Title/button_config_down.png",CC_CALLBACK_0(MainMenu::config, this));
	buttonConfig->setPosition(Vec2(1114, visibleSize.height - 393));

	auto buttonExit = MenuItemImage::create("/ui/Title/button_exit.png", "/ui/Title/button_exit_down.png",CC_CALLBACK_1(MainMenu::menuExit, this));
	buttonExit->setPosition(Vec2(1114, visibleSize.height - 443)); 

	auto menu = Menu::create(buttonNew, buttonLoad, buttonCG, buttonConfig, buttonExit, NULL);
	menu->setPosition(Vec2::ZERO);



	backgroundLayer->addChild(backgroundEffect1, 0);
	backgroundLayer->addChild(backgroundEffect2, 1);
	backgroundLayer->addChild(gameTitle, 3);

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
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void MainMenu::config()
{
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(SettingScene::createScene());
}
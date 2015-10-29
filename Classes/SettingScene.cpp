#include "SettingScene.h"
#include "Control/Slidebar.h"

SettingScene::SettingScene()
{
}


SettingScene::~SettingScene()
{
}

Scene* SettingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SettingScene::create();

	scene->addChild(layer);

	return scene;
}

bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stageLayer = Layer::create();
	
	
	/*加载背景*/
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	stageLayer->addChild(backgroundLayer);

	auto backgroundImage = Sprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	auto backgroundBox = Sprite::create("/ui/config/window_bg.png");
	backgroundBox->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundBox);
	
	/*加载按钮*/

	//SliderBar
	auto textSpeedSliderBar = Slidebar::createSlidebar("/ui/scroll_bar.png", "/ui/scroll_point.png");
	textSpeedSliderBar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(textSpeedSliderBar);
	//

	//返回按钮
	auto buttonBack = MenuItemImage::create("/ui/button_return.png", "/ui/button_return_down.png", CC_CALLBACK_0(SettingScene::back, this));
	buttonBack->setPosition(Vec2(175, 90));
	auto menu = Menu::create(buttonBack, NULL);
	menu->setPosition(Vec2::ZERO);
	stageLayer->addChild(menu);
	
	this->addChild(stageLayer);
	
	return true;
}

void SettingScene::back()
{
	Director::getInstance()->popScene();
}
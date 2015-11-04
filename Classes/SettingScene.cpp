#include "SettingScene.h"
#include "Control/Slidebar.h"

#include "Control/EasyButton.h"
#include "Control/RadioButton.h"

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
	
	
	/*¼ÓÔØ±³¾°*/
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	stageLayer->addChild(backgroundLayer);

	auto backgroundImage = Sprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	auto backgroundBox = Sprite::create("/ui/config/window_bg.png");
	backgroundBox->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundBox);
	
	/*¼ÓÔØ°´Å¥*/

	//SliderBar
	auto textSpeedSliderBar = Slidebar::createSlidebar("/ui/scroll_bar.png", "/ui/scroll_point.png");
	textSpeedSliderBar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(textSpeedSliderBar);

	//

	//²âÊÔ°´Å¥
	auto testButton = EasyButton::createEasyButton("/ui/button_ok.png", "/ui/button_ok.png", "/ui/button_ok_down.png");
	testButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	//stageLayer->addChild(testButton);
	//testButton->touchEvent = CC_CALLBACK_0(SettingScene::back, this);
	auto testButton2 = EasyButton::createEasyButton("/ui/button_ok.png", "/ui/button_ok.png", "/ui/button_ok_down.png");
	testButton2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y + 100));
	//stageLayer->addChild(testButton2);
	auto testButton3 = EasyButton::createEasyButton("/ui/button_ok.png", "/ui/button_ok.png", "/ui/button_ok_down.png");
	testButton3->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y + 100));
	//stageLayer->addChild(testButton3);
	auto testRadio = RadioButton::createRadioButton(testButton, testButton2, testButton3, nullptr);
	stageLayer->addChild(testRadio);


	//·µ»Ø°´Å¥
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
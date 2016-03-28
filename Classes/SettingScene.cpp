#include "SettingScene.h"
#include "GameSystem.h"
#include "SimpleAudioEngine.h"
#include "Control/RadioButton.h"
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
	
	
	/*¼ÓÔØ±³¾°*/
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	stageLayer->addChild(backgroundLayer);

	auto backgroundImage = Sprite::create("ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	auto backgroundBox = Sprite::create("ui/config/window_bg.png");
	backgroundBox->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundBox);
	
	/*¼ÓÔØ°´Å¥*/

	//SliderBar
	_musicVolumeSlidebar = Slidebar::createSlidebar("ui/scroll_bar.png", "ui/scroll_point.png");
	_musicVolumeSlidebar->setPosition(Vec2(750, 400));
	_musicVolumeSlidebar->setFloat(GameSystem::getInstance()->getMusicVolume());
	_musicVolumeSlidebar->moveEvent = CC_CALLBACK_0(SettingScene::changeMusicVolume, this);
	_musicVolumeSlidebar->touchEvent = CC_CALLBACK_0(SettingScene::changeMusicVolume, this);
	stageLayer->addChild(_musicVolumeSlidebar);
	
	//

	//²âÊÔ°´Å¥
	auto testButton = EasyButton::createEasyButton("ui/charbox_off.png", "ui/charbox_off.png", "ui/charbox_on.png");
	testButton->setPosition(Vec2(710, 275));
	auto testButton2 = EasyButton::createEasyButton("ui/charbox_off.png", "ui/charbox_off.png", "ui/charbox_on.png");
	testButton2->setPosition(Vec2(920, 275));

	_testRadio = RadioButton::createRadioButton(testButton, testButton2, nullptr);
	_testRadio->setSelectedNumber(1);
	stageLayer->addChild(_testRadio);
	_testRadio->touchEvent = CC_CALLBACK_0(SettingScene::test, this);



	//·µ»Ø°´Å¥
	auto buttonBack = MenuItemImage::create("ui/button_return.png", "ui/button_return_down.png", CC_CALLBACK_0(SettingScene::back, this));
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

void SettingScene::test()
{
	log("RadioButton Number: %d", _testRadio->getSelectedNumber());
}

void SettingScene::changeMusicVolume()
{
	log("Music Value : %f", _musicVolumeSlidebar->getFloat());
	GameSystem::getInstance()->setMusicVolume(_musicVolumeSlidebar->getFloat());
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameSystem::getInstance()->getMusicVolume());
}
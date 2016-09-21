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
	
	
	/*加载背景*/
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	stageLayer->addChild(backgroundLayer);

    /*
	auto backgroundImage = Sprite::create("ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);
     */
    
	auto backgroundBox = Sprite::create("ui/config/bg_config.jpg");
	backgroundBox->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundBox);
	
	/*加载按钮*/

	//SliderBar
    _textSpeedSlb = Slidebar::createSlidebar("ui/config/slb_background.png", "ui/config/slb_ball.png");
    _textSpeedSlb->setPosition(Vec2(825 + origin.x, 510 + origin.y));
    _textSpeedSlb->setFloat(GameSystem::getInstance()->getTextSpeed());
    _textSpeedSlb->moveEvent = CC_CALLBACK_0(SettingScene::changeTextSpeed, this);
    _textSpeedSlb->touchEvent = CC_CALLBACK_0(SettingScene::changeTextSpeed, this);
    stageLayer->addChild(_textSpeedSlb);
	
    _autoSpeedSlidebar = Slidebar::createSlidebar("ui/config/slb_background.png", "ui/config/slb_ball.png");
    _autoSpeedSlidebar->setPosition(Vec2(825 + origin.x, 442 + origin.y));
    _autoSpeedSlidebar->setFloat(GameSystem::getInstance()->getAutoSpeed());
    _autoSpeedSlidebar->moveEvent = CC_CALLBACK_0(SettingScene::changeAutoSpeed, this);
    _autoSpeedSlidebar->touchEvent = CC_CALLBACK_0(SettingScene::changeAutoSpeed, this);
    stageLayer->addChild(_autoSpeedSlidebar);

    _musicVolumeSlidebar = Slidebar::createSlidebar("ui/config/slb_background.png", "ui/config/slb_ball.png");
    _musicVolumeSlidebar->setPosition(Vec2(825 + origin.x, 374 + origin.y));
    _musicVolumeSlidebar->setFloat(GameSystem::getInstance()->getMusicVolume());
    _musicVolumeSlidebar->moveEvent = CC_CALLBACK_0(SettingScene::changeMusicVolume, this);
    _musicVolumeSlidebar->touchEvent = CC_CALLBACK_0(SettingScene::changeMusicVolume, this);
    stageLayer->addChild(_musicVolumeSlidebar);
    
    /*
    _skipSpeedSlidebar = Slidebar::createSlidebar("ui/config/slb_background.png", "ui/config/slb_ball.png");
    _skipSpeedSlidebar->setPosition(Vec2(712,280));
    stageLayer->addChild(_skipSpeedSlidebar);
     */
    
    _soundVolumeSlidebar = Slidebar::createSlidebar("ui/config/slb_background.png", "ui/config/slb_ball.png");
    _soundVolumeSlidebar->setPosition(Vec2(825 + origin.x, 306 + origin.y));
    _soundVolumeSlidebar->setFloat(GameSystem::getInstance()->getSoundVolume());
    _musicVolumeSlidebar->moveEvent = CC_CALLBACK_0(SettingScene::changeSoundVolume, this);
    _musicVolumeSlidebar->touchEvent = CC_CALLBACK_0(SettingScene::changeSoundVolume, this);
    stageLayer->addChild(_soundVolumeSlidebar);
    
	//

	auto ebSkipReadOnly = EasyButton::createEasyButton("ui/charbox_off.png", "ui/charbox_off.png", "ui/config/yes.png");
	ebSkipReadOnly->setPosition(Vec2(740, 212));
	auto ebSkipAll = EasyButton::createEasyButton("ui/charbox_off.png", "ui/charbox_off.png", "ui/config/yes.png");
	ebSkipAll->setPosition(Vec2(940, 212));
    
	_isSkipAll = RadioButton::createRadioButton(ebSkipReadOnly, ebSkipAll,nullptr);
	_isSkipAll->setSelectedNumber(1);
	stageLayer->addChild(_isSkipAll);
	//_isSkipAll->touchEvent = CC_CALLBACK_0(SettingScene::test, this);
    
    
	//返回按钮
	auto buttonBack = MenuItemImage::create("ui/config/btn_back_normal.png", "ui/config/btn_backtouch.png", CC_CALLBACK_0(SettingScene::back, this));
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

void SettingScene::changeMusicVolume()
{
	log("Music Value : %f", _musicVolumeSlidebar->getFloat());
	GameSystem::getInstance()->setMusicVolume(_musicVolumeSlidebar->getFloat());
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameSystem::getInstance()->getMusicVolume());
}

void SettingScene::changeSoundVolume()
{
    GameSystem::getInstance()->setSoundVolume(_soundVolumeSlidebar->getFloat());
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(GameSystem::getInstance()->getSoundVolume());
}

void SettingScene::changeTextSpeed()
{
    GameSystem::getInstance()->setTextSpeed(_textSpeedSlb->getFloat());
}

void SettingScene::changeAutoSpeed()
{
    GameSystem::getInstance()->setAutoSpeed(_autoSpeedSlidebar->getFloat());
}

void SettingScene::changeIsSkipAll()
{
    if (_isSkipAll->getSelectedNumber())
    {
        GameSystem::getInstance()->setIsSkipAll(false);
    }
    else
    {
        
    }
}

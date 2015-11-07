#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameSystem.h"


USING_NS_CC;

GameScene::GameScene() :_label(nullptr), _backgroundSprite(nullptr)
{

}


GameScene::~GameScene()
{
	delete _reader;
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stageLayer = Layer::create();
	addChild(stageLayer);

	//对话框
	auto _dialogWindow = Sprite::create("/ui/dialog/dialog_bg.png");
	_dialogWindow->setPosition(Vec2(visibleSize.width / 2, 110));
	this->addChild(_dialogWindow);

	//文本框
	_nameLabel = Label::createWithSystemFont("", "微软雅黑", 24);
	_nameLabel->setColor(Color3B::BLACK);
	_nameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_nameLabel->setPosition(70, _dialogWindow->getContentSize().height - 40);
	_dialogWindow->addChild(_nameLabel);

	_textLabel = CharLabel::create("", 24, CC_CALLBACK_0(GameScene::showClickSign, this));
	_textLabel->setPosition(_nameLabel->getPositionX(), _nameLabel->getPositionY() - 25);
	_textLabel->setColor(Color3B::BLACK);
	_dialogWindow->addChild(_textLabel);

	//背景层
	_backgroundLayer = Layer::create();
	//_backgroundLayer->setLocalZOrder(0);
	this->addChild(_backgroundLayer, -1);

	/*
	_label = Label::createWithSystemFont("", "微软雅黑", 24);
	_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_label->setPosition(Vec2(100, 180));
	_label->setColor(Color3B::BLACK);
	_label->retain();
	this->addChild(_label, 200);
	*/

	//对话框按钮
	auto buttonDict = MenuItemImage::create("/ui/dialog/button_dict.png", "/ui/dialog/button_dict_down.png", CC_CALLBACK_0(GameScene::startAutoPlay, this));
	buttonDict->setPosition(Vec2(840,220));

	auto buttonSave = MenuItemImage::create("/ui/dialog/button_save.png", "/ui/dialog/button_save_down.png");
	buttonSave->setPosition(Vec2(900,220));

	auto buttonLoad = MenuItemImage::create("/ui/dialog/button_load.png", "/ui/dialog/button_load_down.png");
	buttonLoad->setPosition(Vec2(960,220));

	auto buttonLog = MenuItemImage::create("/ui/dialog/button_log.png", "/ui/dialog/button_log_down.png");
	buttonLog->setPosition(Vec2(1020,220));

	auto buttonConfig = MenuItemImage::create("/ui/dialog/button_config.png", "/ui/dialog/button_config_down.png");
	buttonConfig->setPosition(Vec2(1080,220));

	auto buttonTitle = MenuItemImage::create("/ui/dialog/button_title.png", "/ui/dialog/button_title_down.png");
	buttonTitle->setPosition(Vec2(1200,220));

	auto CBskip = ui::CheckBox::create("/ui/dialog/charbox_skip_off.png", "/ui/dialog/charbox_skip_off.png", "/ui/dialog/charbox_skip_on.png", "/ui/dialog/charbox_skip_off.png", "/ui/dialog/charbox_skip_on.png");
	CBskip->setPosition(Vec2(1000, 125));
	_dialogWindow->addChild(CBskip, 0);

	auto CBauto = ui::CheckBox::create("/ui/dialog/charbox_auto_off.png", "/ui/dialog/charbox_auto_off.png", "/ui/dialog/charbox_auto_on.png", "/ui/dialog/charbox_auto_off.png", "/ui/dialog/charbox_auto_on.png");
	CBauto->setPosition(Vec2(1000, 75));
	/*
	CBauto->onTouchEnded = [=](Touch *touch, Event *unusedEvent)
	{
		//startAutoPlay();
	};
	*/
	_dialogWindow->addChild(CBauto, 1);

	auto menu = Menu::create(buttonDict, buttonSave, buttonLoad, buttonLog, buttonConfig, buttonTitle, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);



	//监听器
	auto clickEvent = EventListenerTouchOneByOne::create();
	clickEvent->onTouchBegan = [=](Touch *t, Event *e)
	{
		this->screenClicked();
		return false;
	};
	stageLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(clickEvent, stageLayer);

	auto dialogClickEvent = EventListenerTouchOneByOne::create();
	dialogClickEvent->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (_dialogWindow->getBoundingBox().containsPoint(_dialogWindow->convertTouchToNodeSpace(t)))
		{
			this->dialogClicked();
		}
		return true;
	};
	_dialogWindow->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dialogClickEvent, _dialogWindow);

	//创建ScriptReader对象
	_reader = new ScriptReader();
	_reader->initWithStage(stageLayer);
	//绑定reader功能
	_reader->showText = CC_CALLBACK_1(GameScene::showText, this);
	_reader->showName = CC_CALLBACK_1(GameScene::showName, this);
	_reader->changeBackground = CC_CALLBACK_1(GameScene::changeBackground, this);
	_reader->playBackgroundMusic = CC_CALLBACK_1(GameScene::playBackgroundMusic, this);
	_reader->stopBackgroundMusic = CC_CALLBACK_0(GameScene::stopBackgroundMusic, this);
	_reader->playSound = CC_CALLBACK_1(GameScene::playSound, this);
	_reader->stopSound = CC_CALLBACK_0(GameScene::stopSound, this);

	_reader->loadScriptFile("/scenario/TestII.txt");
	_reader->nextScript();
	

	return true;
}

void GameScene::update(float dt)
{
}

void GameScene::updateLabel(std::string text)
{
	_label->setString(text);
}

void GameScene::showClickSign()
{

}

void GameScene::screenClicked()
{
	//_reader->nextScript();
}

void GameScene::dialogClicked()
{
	_reader->nextScript();
}

void GameScene::showName(std::string &name)
{
	_nameLabel->setString(name);
}

void GameScene::showText(std::string &text)
{
	_textLabel->setString(text);
}
void GameScene::changeBackground(Sprite &background)
{
	(&background)->setOpacity(0);
	_backgroundLayer->addChild(&background);
	(&background)->runAction(Sequence::createWithTwoActions(FadeIn::create(1.0f), CallFunc::create([&]()
	{
		if (_backgroundSprite)
		{
			auto *tmp = _backgroundSprite;
			_backgroundSprite = (&background);
			tmp->removeFromParent();
		}
		else
		{
			_backgroundSprite = (&background);
		}
	}
		)
		));

}

void GameScene::playBackgroundMusic(std::string &file)
{
	stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(file.c_str(), true);
	_isPlayingMusic = true;
}

void GameScene::stopBackgroundMusic()
{
	if (_isPlayingMusic)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		_isPlayingMusic = false;
	}
}

void GameScene::scheduleVolumeFadeIn()
{

}

void GameScene::scheduleVolumeFadeOut()
{

}

void GameScene::playSound(std::string &file)
{
	stopSound();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(file.c_str());
}

void GameScene::stopSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void GameScene::startAutoPlay()
{
	//schedule(schedule_selector(GameScene::autoPlay), GameSystem::getInstance()->getAutoSpeed());
	schedule(schedule_selector(GameScene::autoPlay),1.0f);
}

void GameScene::stopAutoPlay()
{
	unschedule(schedule_selector(GameScene::autoPlay));
}

void GameScene::autoPlay(float dt)
{
	_reader->nextScript();
}
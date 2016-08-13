#include "GameScene.h"

#include "SimpleAudioEngine.h"
#include "GameSystem.h"
#include "ScriptReader/BackgroundManager.h"
#include "ScriptReader/BackgroundMusicManager.h"
#include "ScriptReader/SoundManager.h"
#include "SaveScene.h"
#include "LoadScene.h"
#include "HistoryScene.h"
#include "History.hpp"

#define SCRIPT_FILE "scenario/LD.txt"

USING_NS_CC;

GameScene::GameScene() 
	:_label(nullptr)
	, _backgroundSprite(nullptr)
	, _charNumber(0)
	, _backgroundKey("")
	, _backgroundMusicKey("")
	, _soundKey("")
	, _currentName("")
	, _currentText("")
	//, _currentOptions(nullptr)
	, _optionsNumber(0)
{
	_emptyChar = new Charactor;
}


GameScene::~GameScene()
{
	delete _emptyChar;
	_emptyChar = nullptr;
	for (int i = 0; i < MAX_CHARACTOR_NUMBER; i++)
	{
		if (_chars[i])
		{
            if (_chars[i]->faceSprite)
            {
                _chars[i]->leave();
            }
            //delete _chars[i];
			_chars[i] = nullptr;
		}
	}
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
	addChild(stageLayer,13);

	//背景层
	_backgroundLayer = Layer::create();
	//_backgroundLayer->setLocalZOrder(0);
	this->addChild(_backgroundLayer, -1);

	//立绘层
	_charactorsLayer = Layer::create();
	this->addChild(_charactorsLayer, 1);
	for (int i = 0; i < 5; i++)
	{
		_chars[i] = new Charactor;
	}

	//对话框
	_dialogWindow = Sprite::create("ui/dialog/dialog_bg.png");
    _dialogWindow->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_dialogWindow->setPosition(Vec2(visibleSize.width / 2, 176));
	this->addChild(_dialogWindow,10);

    //wtIcon
    _wtIcon = Sprite::create("ui/wait_point.png");
    _wtIcon->setPosition(Vec2(950, 65));
    _wtIcon->setOpacity(0);
    _dialogWindow->addChild(_wtIcon);
    
	//文本框
	_nameLabel = Label::createWithSystemFont("", "微软雅黑", 30);
	_nameLabel->setColor(Color3B::WHITE);
	_nameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_nameLabel->setPosition(140, 190);
	_dialogWindow->addChild(_nameLabel,11);
    
    _nameWindow = Sprite::create("ui/dialog/dialog_name.png");
    _nameWindow->setPosition(170,190);
    _nameWindow->setOpacity(0);
    _dialogWindow->addChild(_nameWindow,10);

	_textLabel = CharLabel::create("", 30, CC_CALLBACK_0(GameScene::showWaittingAnime, this));
	//_textLabel->setPosition(_nameLabel->getPositionX(), _nameLabel->getPositionY() - 25);
    _textLabel->setPosition(104,150);
	_textLabel->setColor(Color3B::WHITE);
    //_textLabel->setCharLabelSize(800, 200);
    _textLabel->setContentSize(Size(TEXTLABEL_SIZE_WIDTH, TEXTLABEL_SIZE_HEIGHT));
	_dialogWindow->addChild(_textLabel,12);

	//对话框按钮
	//auto buttonDict = MenuItemImage::create("ui/dialog/button_dict.png", "ui/dialog/button_dict_down.png", CC_CALLBACK_0(GameScene::startAutoPlay, this));
	//buttonDict->setPosition(Vec2(840,220));

	auto buttonSave = MenuItemImage::create("ui/dialog/save.png", "ui/dialog/save_on.png", CC_CALLBACK_0(GameScene::showSaveScene, this));
    buttonSave->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	buttonSave->setPosition(Vec2(600,20));

	auto buttonLoad = MenuItemImage::create("ui/dialog/load.png", "ui/dialog/load_on.png", CC_CALLBACK_0(GameScene::showLoadScene, this));
    buttonLoad->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	buttonLoad->setPosition(Vec2(680,20));

	auto buttonLog = MenuItemImage::create("ui/dialog/log.png", "ui/dialog/log_on.png", CC_CALLBACK_0(GameScene::showHistoryScene, this));
    buttonLog->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	buttonLog->setPosition(Vec2(920,20));

    //auto buttonConfig = MenuItemImage::create("ui/dialog/button_config.png", "ui/dialog/button_config_down.png",CC_CALLBACK_0(GameScene::startSkipPlay, this));
	//buttonConfig->setPosition(Vec2(1080,220));

    auto buttonTitle = MenuItemImage::create("ui/dialog/menu.png", "ui/dialog/menu_on.png", CC_CALLBACK_0(GameScene::stopAutoPlay, this));
    buttonTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	buttonTitle->setPosition(Vec2(1000,20));

	CBskip = ui::CheckBox::create("ui/dialog/skip_off.png", "ui/dialog/skip_off.png", "ui/dialog/skip_on.png", "ui/dialog/skip_off.png", "ui/dialog/skip_on.png");
	CBskip->setPosition(Vec2(840, 20));
    CBskip->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    CBskip->addEventListener(CC_CALLBACK_2(GameScene::selectEventOfSkip, this));
	this->addChild(CBskip, 13);

	CBauto = ui::CheckBox::create("ui/dialog/auto_off.png", "ui/dialog/auto_off.png", "ui/dialog/auto_on.png", "ui/dialog/auto_off.png", "ui/dialog/auto_on.png");
    CBauto->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	CBauto->setPosition(Vec2(760, 20));
    CBauto->addEventListener(CC_CALLBACK_2(GameScene::selectEventOfAuto, this));
    this->addChild(CBauto, 13);

	auto menu = Menu::create(buttonSave, buttonLoad, buttonLog, buttonTitle, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 13);

	//选项层
	_selectLayer = Layer::create();
	this->addChild(_selectLayer, 13);


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
	//_dialogWindow->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dialogClickEvent, _dialogWindow);

	//创建ScriptReader对象
	
	ScriptReader::getInstance()->initWithStage(stageLayer);
	//绑定reader功能
    
	ScriptReader::getInstance()->showText = CC_CALLBACK_1(GameScene::showText, this);
	ScriptReader::getInstance()->showName = CC_CALLBACK_1(GameScene::showName, this);
	ScriptReader::getInstance()->changeBackground = CC_CALLBACK_1(GameScene::changeBackground, this);
	ScriptReader::getInstance()->playBackgroundMusic = CC_CALLBACK_1(GameScene::playBackgroundMusic, this);
	ScriptReader::getInstance()->stopBackgroundMusic = CC_CALLBACK_0(GameScene::stopBackgroundMusic, this);
	ScriptReader::getInstance()->playSound = CC_CALLBACK_1(GameScene::playSound, this);
	ScriptReader::getInstance()->stopSound = CC_CALLBACK_0(GameScene::stopSound, this);
	ScriptReader::getInstance()->showCharator = CC_CALLBACK_2(GameScene::displayCharator, this);
	ScriptReader::getInstance()->hideCharator = CC_CALLBACK_1(GameScene::unDisplayCharator, this);
	ScriptReader::getInstance()->showSelect = CC_CALLBACK_1(GameScene::showSelect, this);

	ScriptReader::getInstance()->loadScriptFile(SCRIPT_FILE);
    
     
	if (!GameSystem::getInstance()->getIsLoadSuccess())
	{
		ScriptReader::getInstance()->nextScript();
	}
	else
	{
		clear();
		reloadScene();
		GameSystem::getInstance()->setIsLoadSuccess(false);
	}

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
	//ScriptReader::getInstance()->nextScript();
    dialogClicked();
}

void GameScene::dialogClicked()
{
    skipAction();
    if(_textLabel->isRunning())
    {
        _textLabel->finishShow();
        return;
    }
    hideWaittingAnime();
	ScriptReader::getInstance()->nextScript();
}

void GameScene::showName(std::string &name)
{
	_currentName = name;
	_nameLabel->setString(name);
    if (name.compare("") == 0)
    {
        _nameWindow->setOpacity(0);
    }
    else
    {
        _nameWindow->setOpacity(255);
    }
}

void GameScene::showText(std::string &text)
{
	_currentText = text;
	_textLabel->setString(text);
}
void GameScene::changeBackground(std::string &key)
{
	auto background = BM->getBackground(key);
	if (background.compare("") == 0) return;	//如果找不到就退出
	_backgroundKey = key;
	auto backgroundSprite = Sprite::create(background);
	backgroundSprite->setAnchorPoint(Vec2(0, 0));
	backgroundSprite->setOpacity(0);
	_backgroundLayer->addChild(backgroundSprite);
    //auto mtAction = FadeIn::create(0.8f);
    //mtAction->setTag(1);
    auto mtAction = Sequence::createWithTwoActions(FadeIn::create(0.8f), CallFunc::create([&]()
                                                                                                          {
                                                                                                              if (_backgroundSprite)
                                                                                                              {
                                                                                                                  //auto tmp = _backgroundSprite;
                                                                                                                  _backgroundSprite = backgroundSprite;
                                                                                                                  //tmp->removeFromParent();
                                                                                                              }
                                                                                                              else
                                                                                                              {
                                                                                                                  _backgroundSprite = backgroundSprite;
                                                                                                              }
                                                                                                          }
                                                                                                          )
                                                                   );
    mtAction->setTag(1);
	backgroundSprite->runAction(mtAction);
}

void GameScene::playBackgroundMusic(std::string &key)
{
	stopBackgroundMusic();
	auto bgm = BMM->getBackgroundMusic(key);
	if (bgm.compare("") == 0)
	{
		log("Unfine bgm %s", key.c_str());
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgm.c_str(), true);
    if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    log("Playing BGM %s",bgm.c_str());
	_isPlayingMusic = true;
	_backgroundMusicKey = key;
}

void GameScene::stopBackgroundMusic()
{
	if (_isPlayingMusic)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		_isPlayingMusic = false;
		_backgroundMusicKey = "";
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

void GameScene::startSkipPlay()
{
    //schedule(schedule_selector(GameScene::autoPlay),0.01f);
    if (true)
    {
        log("start skip");
        if(ScriptReader::getInstance()->getIsHaveRead())
        {
            log("IsHaveRead");
            schedule(schedule_selector(GameScene::skipPlay),0.01f);
        }
        
    }
    else
    {
        schedule(schedule_selector(GameScene::autoPlay),0.01f);
    }
}

void GameScene::stopSkipPlay()
{
    unschedule(schedule_selector(GameScene::skipPlay));
}

void GameScene::autoPlay(float dt)
{
	dialogClicked();
}
                     
void GameScene::skipPlay(float dt)
{
    log("Skiping");
    if(!ScriptReader::getInstance()->getIsHaveRead())
    {
        log("Stop skiping!");
        CBskip->setSelected(false);
        stopSkipPlay();
    }
    dialogClicked();
}

void GameScene::createGameDate()
{
	auto tmpGameData = new GameData;
	tmpGameData->backgroundKey = _backgroundKey;
	tmpGameData->bgmKey = _backgroundMusicKey;
	tmpGameData->soundKey = _soundKey;
	tmpGameData->charactorCount = _charNumber;
	int n = 0;
	for (int i = 0; i < MAX_CHARACTOR_NUMBER; i++)
	{
		if (_chars[i]->faceSprite)
		{
			tmpGameData->fgCharactors[n].name = _chars[i]->key;
			tmpGameData->fgCharactors[n].face = _chars[i]->currentFace;
			tmpGameData->fgCharactors[n].number = i;
			n++;
		}
	}
	tmpGameData->currentCommandIndex = ScriptReader::getInstance()->getCurrentCommandIndex();
	tmpGameData->currentSignName = ScriptReader::getInstance()->getCurrentSignName();
	tmpGameData->currentName = _currentName;
	tmpGameData->currentText = _currentText;
	tmpGameData->optionsNumber = _optionsNumber;
	
	if(_optionsNumber)
	{
		log("Select::> optionSize[%d]", _currentOptions.size());
		tmpGameData->options.insert(_currentOptions.begin(), _currentOptions.end());
	}
		//tmpGameData->options = *_currentOptions;
	
	GameSystem::getInstance()->setGameSceneInfo(tmpGameData);
}

void GameScene::displayCharator(std::string cName, std::string face)
{
	auto cha = CM->getCharactor(cName);	//获取角色
    log("cName = %s, Name = %s",cName.c_str(),cha->name.c_str());
	if (cha && cha->getCharactorFace(face))
	{
		bool isNeedShow = false;	//判断是否需要重新显示人物立绘
		if (cha->faceSprite)
		{
			log("CurrentFace = %s, Face = %s", cha->currentFace.c_str(), face.c_str());
			if (cha->currentFace != face && face.compare("") != 0)
			{
				cha->leave();
				isNeedShow = true;
			}
		}
		else
		{
			isNeedShow = true;
		}



		if (isNeedShow)
		{
			auto pChar = &_chars[2];
			CMPositionType tmpPT = CMPositionType::EMPTY;

			Sprite *sp = nullptr;
			if (cha->getCharactorFace(face))
				sp = Sprite::create(cha->getCharactorFace(face));
			cha->faceSprite = sp;
			cha->key = cName;
			cha->currentFace = face;
			if (face.compare("") != 0)
			{
				if (!_charNumber)
				{
					_charNumber++;
					pChar = &_chars[2];
					tmpPT = CMPositionType::CENTER;
				}
				else
					if (_charNumber == 1)
					{
						if (_chars[2] == cha)
						{
							pChar = &_chars[2];
							tmpPT = CMPositionType::CENTER;
						}
						else
						{
							_chars[2]->moveTo(CMPositionType::LEFT_CENTER);
							_chars[1] = _chars[2];
							_chars[2] = _emptyChar;
							_charNumber++;
							pChar = &_chars[3];
							tmpPT = CMPositionType::RIGHT_CENTER;
						}
					}
					else
					{
						if (_charNumber == 2)
						{
							if (_chars[1] == cha)
							{
								pChar = &_chars[1];
								tmpPT = CMPositionType::LEFT_CENTER;
							}
							else
								if (_chars[3] == cha)
								{
									pChar = &_chars[3];
									tmpPT = CMPositionType::RIGHT_CENTER;
								}
								else
								{
									_chars[1]->moveTo(CMPositionType::LEFT);
									_chars[0] = _chars[1];
									_chars[1] = _emptyChar;
									_chars[3]->moveTo(CMPositionType::RIGHT);
									_chars[4] = _chars[3];
									_chars[3] = _emptyChar;
									_charNumber++;
									pChar = &_chars[2];
									tmpPT = CMPositionType::CENTER;
								}
						}
						else
						{
							if (_chars[0] == cha)
							{
								pChar = &_chars[0];
								tmpPT = CMPositionType::LEFT;
							}
							else
								if (_chars[2] == cha)
								{
									pChar = &_chars[2];
									tmpPT = CMPositionType::CENTER;
								}
								else
									if (_chars[4] == cha)
									{
										pChar = &_chars[4];
										tmpPT = CMPositionType::RIGHT;
									}
									else
									{
										pChar = &_chars[2];
										tmpPT = CMPositionType::CENTER;
									}
						}
					}

                /*
				if (((Charactor*)*pChar))
				{
					((Charactor*)*pChar)->leave();
				}
                */
                
                Size visibleSize = Director::getInstance()->getVisibleSize();

				cha->currentPosition = tmpPT;
				if (sp)
                {
					*pChar = cha;
                }

				switch (tmpPT)
				{
				case CMPositionType::LEFT:
				{
					sp->setPositionX(visibleSize.width / 4);
					break;
				}
				case CMPositionType::LEFT_CENTER:
				{
					sp->setPositionX(visibleSize.width / 3);
					break;
				}
				case CMPositionType::CENTER:
				{
					sp->setPositionX(visibleSize.width / 2);
					break;
				}
				case CMPositionType::RIGHT_CENTER:
				{
					sp->setPositionX(visibleSize.width * 2 / 3);
					break;
				}
				case CMPositionType::RIGHT:
				{
					sp->setPositionX(visibleSize.width *3 / 4);
					break;
				}
				default:
				{
					break;
				}
				}

				sp->setAnchorPoint(Vec2(0.5, 0));

				_charactorsLayer->addChild(sp);
			}
		}
	}
}

void GameScene::unDisplayCharator(std::string cName)
{
	auto cha = CM->getCharactor(cName);
	if (cha->faceSprite)
	{
		auto mtAction = Sequence::createWithTwoActions(FadeOut::create(0.8f), CallFunc::create([=]()
		{
			if (_charNumber == 1)
			{
				_chars[2] = _emptyChar;
			}
			else
				if (_charNumber == 2)
				{
					switch (cha->currentPosition)
					{
					case CMPositionType::LEFT_CENTER:
					{
						_chars[1] = _emptyChar;
						_chars[3]->moveTo(CMPositionType::CENTER);
						_chars[2] = _chars[3];
						_chars[3] = _emptyChar;
						break;
					}
					case CMPositionType::RIGHT_CENTER:
					{
						_chars[3] = _emptyChar;
						_chars[1]->moveTo(CMPositionType::CENTER);
						_chars[2] = _chars[1];
						_chars[1] = _emptyChar;
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
					if (_charNumber == 3)
					{
						switch (cha->currentPosition)
						{
						case CMPositionType::LEFT:
						{
							_chars[0] = _emptyChar;
							_chars[2]->moveTo(CMPositionType::LEFT_CENTER);
							_chars[1] = _chars[2];
							_chars[2] = _emptyChar;
							_chars[4]->moveTo(CMPositionType::RIGHT_CENTER);
							_chars[3] = _chars[4];
							_chars[4] = _emptyChar;
							break;
						}
						case CMPositionType::CENTER:
						{
							_chars[2] = _emptyChar;
							_chars[0]->moveTo(CMPositionType::LEFT_CENTER);
							_chars[1] = _chars[0];
							_chars[0] = _emptyChar;
							_chars[4]->moveTo(CMPositionType::RIGHT_CENTER);
							_chars[3] = _chars[4];
							_chars[4] = _emptyChar;
							break;
						}
						case CMPositionType::RIGHT:
						{
							_chars[4] = _emptyChar;
							_chars[0]->moveTo(CMPositionType::LEFT_CENTER);
							_chars[1] = _chars[0];
							_chars[0] = _emptyChar;
							_chars[2]->moveTo(CMPositionType::RIGHT_CENTER);
							_chars[3] = _chars[2];
							_chars[2] = _emptyChar;
							break;
						}
						default:
						{
							break;
						}
						}

					}
			cha->leave();
			_charNumber--;
			return;
		}
			)
			);
        mtAction->setTag(1);
        cha->faceSprite->runAction(mtAction);
	}
	else
		return;
}

void GameScene::showSaveScene()
{
	ScreenShoot();
	createGameDate();	//向GameSystem更新GameData信息
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(SaveScene::createScene());
	
	//GameSystem::getInstance()->saveGameSceneInfo(1);
	//this->setScale(1.0f);
}

void GameScene::ScreenShoot()
{
	//utils::captureScreen(nullptr, "savedata\\savedataImage.jpg");

	float scale = 0.1164f;	//缩小倍率
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	auto render = RenderTexture::create(getContentSize().width*scale, getContentSize().height*scale);
	render->begin();
	this->setScale(scale);
	this->visit();
	render->end();
	render->retain();
	GameSystem::getInstance()->setScreenShoot(render);
	this->setScale(1.0f);
}

void GameScene::clear()
{
    log("Clearing");
	/*清除所有立绘*/
	for (int i = 0; i < MAX_CHARACTOR_NUMBER; i++)
	{
        log("_chars[%i]->key = %s",i,_chars[i]->key.c_str());
		if (_chars[i]->faceSprite)
		{
			_chars[i]->leave();
            log("Chars[%i] clear.", i);
		}
	}
	_charNumber = 0;

	/*停止播放音乐*/
	stopBackgroundMusic();

	/*清楚当前背景*/
	//std::string black = "black";
	//changeBackground(black);

	auto backgroundSprite = Sprite::create("bgimage/Black.jpg");
	backgroundSprite->setAnchorPoint(Vec2(0, 0));
	_backgroundLayer->addChild(backgroundSprite);
	_backgroundSprite = backgroundSprite;

	/*停止当前音效*/
	stopSound();

	/*清空当前文本层*/
	std::string empty = "";
	showName(empty);
	showText(empty);

	/*清空选项*/
	if (_optionsNumber)
	{
		_optionsNumber = 0;
		_currentOptions.clear();
		_selectLayer->removeAllChildren();
	}
}

void GameScene::showLoadScene()
{
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(LoadScene::createScene());
}

void GameScene::reloadScene()
{
	if (GameSystem::getInstance()->getIsLoadSuccess())
	{ 
		/*设置背景*/
		auto background = BM->getBackground(GameSystem::getInstance()->getGameSceneInfo()->backgroundKey);
		if (background.compare("") == 0)
        {
            log("ReloadScene> No Background in the savedata.");
			background = "black";
        }
		auto backgroundSprite = Sprite::create(background);
		backgroundSprite->setAnchorPoint(Vec2(0, 0));
		_backgroundLayer->addChild(backgroundSprite);
		_backgroundSprite = backgroundSprite;
		/*设置当前名字*/
		showName(GameSystem::getInstance()->getGameSceneInfo()->currentName);
		/*设置当前文本*/
		showText(GameSystem::getInstance()->getGameSceneInfo()->currentText);
		/*设置当前立绘*/
		_charNumber = GameSystem::getInstance()->getGameSceneInfo()->charactorCount;
		log("load charator");
		for (int i = 0; i < _charNumber; i++)
		{
			auto name = GameSystem::getInstance()->getGameSceneInfo()->fgCharactors[i].name;
			auto face = GameSystem::getInstance()->getGameSceneInfo()->fgCharactors[i].face;
			auto number = GameSystem::getInstance()->getGameSceneInfo()->fgCharactors[i].number;
			auto cha = CM->getCharactor(name);	//获取角色
			if (cha)
			{
				auto pChar = &_chars[number];
				CMPositionType tmpPT = CMPositionType::EMPTY;

				Sprite *sp = nullptr;
				if (cha->getCharactorFace(face))
					sp = Sprite::create(cha->getCharactorFace(face));
				cha->faceSprite = sp;
				cha->key = name;
				cha->currentFace = face;
				switch (number)
				{
				case 0:
					tmpPT = CMPositionType::LEFT;
					break;
				case 1:
					tmpPT = CMPositionType::LEFT_CENTER;
					break;
				case 2:
					tmpPT = CMPositionType::CENTER;
					break;
				case 3:
					tmpPT = CMPositionType::RIGHT_CENTER;
					break;
				case 4:
					tmpPT = CMPositionType::RIGHT;
					break;
				default:
					break;
				}
				if (face.compare("") != 0)
				{

					if (((Charactor*)*pChar))
					{
						((Charactor*)*pChar)->leave();
					}

                    Size visibleSize = Director::getInstance()->getVisibleSize();

					cha->currentPosition = tmpPT;
					if (sp)
						*pChar = cha;

					switch (tmpPT)
					{
					case CMPositionType::LEFT:
					{
						sp->setPositionX(360);
						break;
					}
					case CMPositionType::LEFT_CENTER:
					{
						sp->setPositionX(427);
						break;
					}
					case CMPositionType::CENTER:
					{
						sp->setPositionX(640);
						break;
					}
					case CMPositionType::RIGHT_CENTER:
					{
						sp->setPositionX(853);
						break;
					}
					case CMPositionType::RIGHT:
					{
						sp->setPositionX(960);
						break;
					}
					default:
					{
						break;
					}
					}

					sp->setAnchorPoint(Vec2(0.5, 0));

					_charactorsLayer->addChild(sp);
				}
			}
		}
		/*设置当前播放bgm信息*/
		playBackgroundMusic(GameSystem::getInstance()->getGameSceneInfo()->bgmKey);
		/*设置当前播放音效*/
		/*设置选项信息*/
		log("load select start");
		if (GameSystem::getInstance()->getGameSceneInfo()->optionsNumber)
		{
			showSelect(GameSystem::getInstance()->getGameSceneInfo()->options);
		}
		/*设置ScriptReader*/
		auto sign = GameSystem::getInstance()->getGameSceneInfo()->currentSignName;
		auto commandIndex = GameSystem::getInstance()->getGameSceneInfo()->currentCommandIndex;
		ScriptReader::getInstance()->jumpToSign(sign, commandIndex);
	}
}

void GameScene::showSelect(std::map<std::string, std::string> &options)
{
	_currentOptions = options;

	auto menu = Menu::create();
	int startY = options.size()*(60) / 2;
	int size = options.size();
	log("Select::> optionSize[%d]", options.size());
	for (auto itr = options.begin(); itr != options.end(); itr++)
	{
		_optionsNumber++;	//选择数量+1
		auto label = Label::createWithSystemFont(itr->second, "MSYH", 30);
		label->setColor(Color3B::WHITE);
		label->enableShadow();
		log("OPTION[%s] SIGN[%s]", itr->second.c_str(), itr->first.c_str());
		auto tmp = itr->first;
		auto tmp2 = itr->second;
		auto button = MenuItemLabel::create(label, [=](Ref*)
		{
			HistoryLogger::getInstance()->addRecord("null", tmp2, "");
			ScriptReader::getInstance()->jumpToSign(tmp);
			menu->removeFromParent();
			_currentOptions.clear();
			_optionsNumber = 0;
		});

		menu->addChild(button);
		button->setPosition(0, startY);
		startY -= 60;
	}
	_selectLayer->addChild(menu, 13);
}

void GameScene::showHistoryScene()
{
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(HistoryScene::createScene());
}

void GameScene::skipAction()
{
    //skip Background Action
    auto bgList = _backgroundLayer->getChildren();
    for (auto iter=bgList.begin();iter!=bgList.end();iter++)
    {
        if ((*iter)->getActionByTag(1))
        {
            (*iter)->getActionByTag(1)->step(3.0f);
        }
    }
    //skip Charactor Action
    auto chaList = _charactorsLayer->getChildren();
    for (auto iter=chaList.begin();iter!=chaList.end();iter++)
    {
        if ((*iter)->getActionByTag(1))
        {
            (*iter)->getActionByTag(1)->step(3.0f);
        }
    }
}

void GameScene::showWaittingAnime()
{
    _wtIcon->setOpacity(255);
    auto action = FadeOut::create(0.8f);
    auto actionBack = action->reverse();
    _wtIcon->runAction(RepeatForever::create(Sequence::create(action,actionBack, NULL)));
}

void GameScene::hideWaittingAnime()
{
    _wtIcon->stopAllActions();
    _wtIcon->setOpacity(0);
}

void GameScene::selectEventOfSkip(Ref* pSender,CheckBox::EventType type)
{
    log("CheckBox has active.");
    switch (type) {
        case CheckBox::EventType::SELECTED:
            log("SELECTED");
            startSkipPlay();
            break;
            
        case CheckBox::EventType::UNSELECTED:
            log("UNSELECTED");
            stopSkipPlay();
            break;
        default:
            break;
    }
}

void GameScene::selectEventOfAuto(cocos2d::Ref *pSender, CheckBox::EventType type)
{
    switch (type) {
        case CheckBox::EventType::SELECTED:
            log("SELECTED");
            startAutoPlay();
            break;
            
        case CheckBox::EventType::UNSELECTED:
            log("UNSELECTED");
            stopAutoPlay();
            break;
        default:
            break;
    }
}
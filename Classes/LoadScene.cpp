#include "LoadScene.h"
#include "GameSystem.h"
#include "GameScene.h"
#include "PopupLayer.hpp"

LoadScene::LoadScene()
{
    _currentSelectButton = -1;
}


LoadScene::~LoadScene()
{
}

Scene* LoadScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stageLayer = Layer::create();

	/*���ر���*/
    auto backgroundLayer = LayerColor::create(Color4B::BLACK);
    stageLayer->addChild(backgroundLayer);
    
    auto backgroundWindow = Sprite::create("ui/saveload/save_bg.jpg");
    backgroundWindow->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    stageLayer->addChild(backgroundWindow);
    
    /*���ذ�ť*/
	for (int i = 0; i < 3; i++)
	{
		dataButtons[i] = SaveData::create(i);
		dataButtons[i]->setPosition(116, 368 - 150 * i);
		eventTouch[i] = EventListenerTouchOneByOne::create();
		eventTouch[i]->onTouchBegan = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//�������ָ��
			{
				return true;
			}
			return false;
		};
		eventTouch[i]->onTouchEnded = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//�������ָ��
			{
                _currentSelectButton = i;
				popup();
			}
			else
			{
				
			}
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventTouch[i], this);
		stageLayer->addChild(dataButtons[i]);
	}



	//���ذ�ť
	auto buttonBack = MenuItemImage::create("ui/button_return.png", "ui/button_return_down.png", CC_CALLBACK_0(LoadScene::back, this));
	buttonBack->setPosition(Vec2(175, 90));
	auto menu = Menu::create(buttonBack, NULL);
	menu->setPosition(Vec2::ZERO);
	stageLayer->addChild(menu);

    
	this->addChild(stageLayer);
	return true;
}

void LoadScene::back()
{
	//GameSystem::getInstance()->initGameSavedataList();
	Director::getInstance()->popScene();
}

void LoadScene::popup()
{
    auto result = GameSystem::getInstance()->loadGameSceneInfo(_currentSelectButton);
    if (result)
    {
        //��ʾ��ȡ�浵
        PopupLayer* popupDialog = PopupLayer::create("ui/popup.png");
        popupDialog->addLabelButton("Yes", CC_CALLBACK_0(LoadScene::apply, this));
        popupDialog->addLabelButton("No", CC_CALLBACK_0(LoadScene::cancel, this));
        popupDialog->setString("Are you sure load this file?");
        this->addChild(popupDialog);
    }
}

void LoadScene::apply()
{
    if (_currentSelectButton >= 0)
    {
        log("Loading!");
        GameSystem::getInstance()->setIsLoadSuccess(true);
        if (GameSystem::getInstance()->getGameScene())
        {
            Director::getInstance()->popScene();
        }
        GameSystem::getInstance()->setGameScene(GameScene::createScene());
        auto scene = GameSystem::getInstance()->getGameScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void LoadScene::cancel()
{
    log("cancel.");
    _currentSelectButton = -1;
}
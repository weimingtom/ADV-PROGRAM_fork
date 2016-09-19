#include "SaveScene.h"
#include "GameSystem.h"
#include "PopupLayer.hpp"
#include <stdlib.h>

SaveScene::SaveScene()
{
    _currentSelectButton = -1;
}


SaveScene::~SaveScene()
{
}

Scene* SaveScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SaveScene::create();

	scene->addChild(layer);

	return scene;
}

bool SaveScene::init()
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

	auto backgroundWindow = Sprite::create("ui/sl/bg_save.jpg");
	backgroundWindow->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundWindow);

	/*加载按钮*/

	//dataButtons[8];
	for (int i = 0; i < 4; i++)
	{
		dataButtons[i] = SaveData::create(i);
        dataButtons[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		dataButtons[i]->setPosition(visibleSize.width/2 + origin.x + 50, 530 - 140 * i);
		//dataButtons[i]->onTouchEnded = CC_CALLBACK_1(GameSystem::saveGameSceneInfo, GameSystem::getInstance());
		eventTouch[i] = EventListenerTouchOneByOne::create();
		eventTouch[i]->onTouchBegan = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//如果碰到指针
			{
				return true;
			}
			return false;
		};
		eventTouch[i]->onTouchEnded = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//如果碰到指针
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
	


	//返回按钮
	auto buttonBack = MenuItemImage::create("ui/button_return.png", "ui/button_return_down.png", CC_CALLBACK_0(SaveScene::back, this));
	buttonBack->setPosition(Vec2(175, 90));
	auto menu = Menu::create(buttonBack, NULL);
	menu->setPosition(Vec2::ZERO);
	stageLayer->addChild(menu);


	this->addChild(stageLayer);
	return true;
}

void SaveScene::back()
{
	GameSystem::getInstance()->initGameSavedataList();
	Director::getInstance()->popScene();
}

void SaveScene::popup()
{
    auto result = true;
    if (result)
    {
        //提示读取存档
        PopupLayer* popupDialog = PopupLayer::create("ui/popup.png");
        popupDialog->addLabelButton("Yes", CC_CALLBACK_0(SaveScene::apply, this));
        popupDialog->addLabelButton("No", CC_CALLBACK_0(SaveScene::cancel, this));
        
        char* text = new char[3];
        sprintf(text,"%d",_currentSelectButton+1);
        std::string popupText = "Are you sure save in No." + (std::string)text + " file?";
        popupDialog->setString(popupText);
        this->addChild(popupDialog);
    }
}

void SaveScene::apply()
{
    if (_currentSelectButton >= 0)
    {
        log("Saving!");
        GameSystem::getInstance()->saveGameSceneInfo(_currentSelectButton);
        GameSystem::getInstance()->updateGameSavedata(_currentSelectButton);
        dataButtons[_currentSelectButton]->updataData();
    }
}

void SaveScene::cancel()
{
    log("cancel.");
    _currentSelectButton = -1;
}

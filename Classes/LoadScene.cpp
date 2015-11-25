#include "LoadScene.h"
#include "GameSystem.h"

LoadScene::LoadScene()
{
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

	auto backgroundImage = Sprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	auto backgroundWindow = Sprite::create("/ui/saveload/window_bg.png");
	backgroundWindow->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundWindow);

	/*���ذ�ť*/

	SaveData* dataButtons[8];
	for (int i = 0; i < 4; i++)
	{
		dataButtons[i] = SaveData::create(i);
		dataButtons[i]->setPosition(425, 520 - 115 * i);
		//dataButtons[i]->onTouchEnded = CC_CALLBACK_1(GameSystem::saveGameSceneInfo, GameSystem::getInstance());
		stageLayer->addChild(dataButtons[i]);
	}
	for (int i = 4; i < 8; i++)
	{
		dataButtons[i] = SaveData::create(i);
		dataButtons[i]->setPosition(850, 520 - 115 * (i - 4));
		//dataButtons[i]->onTouchEnded = CC_CALLBACK_1(GameSystem::saveGameSceneInfo, GameSystem::getInstance());
		stageLayer->addChild(dataButtons[i]);
	}



	//���ذ�ť
	auto buttonBack = MenuItemImage::create("/ui/button_return.png", "/ui/button_return_down.png", CC_CALLBACK_0(LoadScene::back, this));
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

void LoadScene::load(int i)
{
	GameSystem::getInstance()->saveGameSceneInfo(i);
}

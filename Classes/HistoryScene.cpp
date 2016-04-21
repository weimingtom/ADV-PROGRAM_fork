#include "HistoryScene.h"
#include "ui/CocosGUI.h"

HistoryMessage::HistoryMessage(std::string text, std::string name, Color4B color)
{
	_nameLabel = Label::createWithSystemFont(name, "����", 20);
	_nameLabel->setColor(Color3B::WHITE);
	_nameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_nameLabel->setPosition(Vec2(-265, 12));
	this->addChild(_nameLabel);

	_textLabel = Label::createWithSystemFont(text, "����", 20);
	_textLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_textLabel->setPosition(Vec2(-265, -12));
	this->addChild(_textLabel);
}


HistoryMessage::~HistoryMessage()
{
}

HistoryMessage* HistoryMessage::create(record* record)
{
	auto text = record->text;
	auto name = record->name;
	auto color = record->color;
	auto tmpHM = new HistoryMessage(text, name, color);
	return tmpHM;
}

HistoryScene::HistoryScene()
{
}


HistoryScene::~HistoryScene()
{
}

Scene* HistoryScene::createScene()
{
	auto scene = Scene::create();

	auto layer = HistoryScene::create();

	scene->addChild(layer);

	return scene;
}

bool HistoryScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stageLayer = Layer::create();
    //stageLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //stageLayer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	/*���ر���*/
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	stageLayer->addChild(backgroundLayer);

	auto backgroundImage = Sprite::create("ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	/*������ʷ��¼*/
	auto historyList = Sprite::create();
    //historyList->cocos2d::Node::setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    historyList->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    
    auto historyListView = ui::ScrollView::create();
    historyListView->setDirection(ui::SCROLLVIEW_DIR_VERTICAL);
    historyListView->setTouchEnabled(true);
    historyListView->setBounceEnabled(true);
    historyListView->setSize(Size(visibleSize.width,visibleSize.height));
    //historyListView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //historyListView->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	int startY = 0;
	for (int i = 0; i < HistoryLogger::getInstance()->getLength(); i++)
	{
		//log("i = %d", i);
		auto record = HistoryLogger::getInstance()->getRecord(i);
		log("Record[%d] = [%s , %s]", i, record->name.c_str(), record->text.c_str());
		auto hm = HistoryMessage::create(record);
		//hm->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        hm->setPosition(0, startY);
        historyList->addChild(hm);
        //historyListView->addChild(hm);
		startY -= hm->getContentSize().height + 50;

	}
    historyListView->addChild(historyList);
    stageLayer->addChild(historyListView);

	/*����ʷ��¼��Ӵ����¼�*/
	/*
	auto et = EventListenerTouchOneByOne::create();
	pointPositionY = historyList->getPosition().y;
	et->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//�������ָ��
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	et->onTouchMoved = [=](Touch *t, Event *e)
	{
		float yOff = t->getLocation().x - t->getStartLocation().x;


		historyList->setPositionY(pointPositionY + yOff);

	};

	et->onTouchEnded = [&](Touch *t, Event *e)
	{
		//����ָ��λ��
		pointPositionY = historyList->getPositionY();
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(et, this);

	*/

	//���ذ�ť
	auto buttonBack = MenuItemImage::create("ui/button_return.png", "/ui/button_return_down.png", CC_CALLBACK_0(HistoryScene::back, this));
	buttonBack->setPosition(Vec2(175 + origin.x, 90 + origin.y));
	auto menu = Menu::create(buttonBack, NULL);
	menu->setPosition(Vec2::ZERO);
	stageLayer->addChild(menu);
    
    auto testS = Sprite::create("ui/cg/cg_bg_unget.png");
    testS->setPosition(Vec2(0,0));
    stageLayer->addChild(testS);

	addChild(stageLayer);

	return true;
}

void HistoryScene::back()
{
	Director::getInstance()->popScene();
}
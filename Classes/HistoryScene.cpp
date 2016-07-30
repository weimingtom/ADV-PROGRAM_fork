#include "HistoryScene.h"
#include "ui/CocosGUI.h"

HistoryMessage::HistoryMessage(std::string text, std::string name, Color4B color)
{
	_nameLabel = Label::createWithSystemFont(name, "黑体", 20);
	_nameLabel->setColor(Color3B::WHITE);
	_nameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_nameLabel->setPosition(Vec2(0, 12));
	this->addChild(_nameLabel);

	_textLabel = Label::createWithSystemFont(text, "黑体", 20);
	_textLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_textLabel->setPosition(Vec2(0, -12));
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

	/*加载背景*/
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	stageLayer->addChild(backgroundLayer);

	auto backgroundImage = Sprite::create("ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	/*加载历史记录*/
	auto historyList = Sprite::create();
    //historyList->cocos2d::Node::setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //historyList->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    historyList->setPosition(Vec2(0, 0));
    
    auto historyListView = ui::ScrollView::create();
    //滚动方向为垂直
    historyListView->setDirection(ui::ScrollView::Direction::VERTICAL);
    //可触碰
    historyListView->setTouchEnabled(true);
    //弹性滚动
    historyListView->setBounceEnabled(true);
    //设置ScrollView大小
    historyListView->setContentSize(Size(visibleSize.width/2,visibleSize.height/2));
    historyListView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    historyListView->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    int startY = 0;//记录下一条历史记录的Y坐标，从上往下，所以Y值一直在减少。
	for (int i = 0; i < HistoryLogger::getInstance()->getLength(); i++)
	{
		//log("i = %d", i);
		auto record = HistoryLogger::getInstance()->getRecord(i);
		log("Record[%d] = [%s , %s]", i, record->name.c_str(), record->text.c_str());
		auto hm = HistoryMessage::create(record);
		//hm->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        hm->setPosition(0, startY);
        historyList->addChild(hm);
        //historyListView->addChild(hm);
		startY -= hm->getContentSize().height + 50;

	}
    //将ScrollView的内层大小设置为和所有历史记录高度一致
    historyListView->setInnerContainerSize(Size(visibleSize.width / 2, abs(startY)));
    //将所有历史记录的位置调整和ScrollView的内层对齐
    historyList->setPosition(Vec2(0, historyListView->getInnerContainerSize().height));
    historyListView->addChild(historyList);
    
    stageLayer->addChild(historyListView);
    //log("startY = %d, abs(startY) = %d, historyList.height = %0.2f, InnerContainerSize.height = %0.2f",startY,abs(startY), historyList->getContentSize().height, historyListView->getInnerContainerSize().height);
    //跳转到最底部，但视乎没有效果。
    historyListView->jumpToBottom();
    
    //使用定时器让下一帧调用
    scheduleOnce([=](float)
    {
        historyListView->jumpToBottom();
    }, 0.01f, "XXX");
	
	//返回按钮
	auto buttonBack = MenuItemImage::create("ui/button_return.png", "/ui/button_return_down.png", CC_CALLBACK_0(HistoryScene::back, this));
	buttonBack->setPosition(Vec2(175 + origin.x, 90 + origin.y));
	auto menu = Menu::create(buttonBack, NULL);
	menu->setPosition(Vec2::ZERO);
	stageLayer->addChild(menu);

	addChild(stageLayer);

	return true;
}

void HistoryScene::back()
{
	Director::getInstance()->popScene();
}
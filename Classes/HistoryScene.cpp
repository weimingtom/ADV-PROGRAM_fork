#include "HistoryScene.h"
#include "ui/CocosGUI.h"

HistoryMessage::HistoryMessage(std::string text, std::string name, Color4B color)
{
	_nameLabel = Label::createWithSystemFont(name, "����", 20);
	_nameLabel->setColor(Color3B::WHITE);
	_nameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_nameLabel->setPosition(Vec2(0, 12));
	this->addChild(_nameLabel);

	_textLabel = Label::createWithSystemFont(text, "����", 20);
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

	/*���ر���*/
	auto backgroundLayer = LayerColor::create(Color4B::BLACK);
	stageLayer->addChild(backgroundLayer);

	auto backgroundImage = Sprite::create("ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	/*������ʷ��¼*/
	auto historyList = Sprite::create();
    //historyList->cocos2d::Node::setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //historyList->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    historyList->setPosition(Vec2(0, 0));
    
    auto historyListView = ui::ScrollView::create();
    //��������Ϊ��ֱ
    historyListView->setDirection(ui::ScrollView::Direction::VERTICAL);
    //�ɴ���
    historyListView->setTouchEnabled(true);
    //���Թ���
    historyListView->setBounceEnabled(true);
    //����ScrollView��С
    historyListView->setContentSize(Size(visibleSize.width/2,visibleSize.height/2));
    historyListView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    historyListView->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    int startY = 0;//��¼��һ����ʷ��¼��Y���꣬�������£�����Yֵһֱ�ڼ��١�
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
    //��ScrollView���ڲ��С����Ϊ��������ʷ��¼�߶�һ��
    historyListView->setInnerContainerSize(Size(visibleSize.width / 2, abs(startY)));
    //��������ʷ��¼��λ�õ�����ScrollView���ڲ����
    historyList->setPosition(Vec2(0, historyListView->getInnerContainerSize().height));
    historyListView->addChild(historyList);
    
    stageLayer->addChild(historyListView);
    //log("startY = %d, abs(startY) = %d, historyList.height = %0.2f, InnerContainerSize.height = %0.2f",startY,abs(startY), historyList->getContentSize().height, historyListView->getInnerContainerSize().height);
    //��ת����ײ������Ӻ�û��Ч����
    historyListView->jumpToBottom();
    
    //ʹ�ö�ʱ������һ֡����
    scheduleOnce([=](float)
    {
        historyListView->jumpToBottom();
    }, 0.01f, "XXX");
	
	//���ذ�ť
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
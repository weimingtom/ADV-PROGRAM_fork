#include "SaveData.h"
#include "GameSystem.h"

#define NO_DATA_IMAGE ""

SaveData::SaveData(int number, std::string imageFile, std::string text, std::string date)
{
	/*���ش浵��ť����*/
	
	/*���ش浵���*/
	
	/*���ش浵��ͼ*/

	/*���ش浵��Ϣ*/

	/*���ر�ע��Ϣ*/
}

SaveData::SaveData(int number)
{
	/*���ذ�ť�ײ�*/
	/*
	auto stageLayer = Layer::create();
	stageLayer->setContentSize(Size(400,110));
	stageLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	*/
	auto stageLayer = Sprite::create("/ui/saveload/noselected_bg.png");


	if (GameSystem::getInstance()->getSavedata(number))
	{
		/*��ʾ�浵���*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		stageLayer->addChild(dataNumber);
		*/

		/*��ʾ�浵��ͼ*/
		std::string imageFile = "imageOfSavedata";
		imageFile = GameSystem::getInstance()->getDataValue(imageFile);

		auto dataImage = Sprite::create(imageFile);
		dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		dataImage->setPosition(19, 99);
		stageLayer->addChild(dataImage);

		/*��ʾ�浵��Ϣ*/
		std::string text = "textOfSavedata";
		text = GameSystem::getInstance()->getDataValue(text);

		auto dataText = Label::createWithSystemFont(text, "����", 20);
		dataText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		dataText->setPosition(160,35);
		stageLayer->addChild(dataText);

		/*��ʾ�浵����*/
		std::string date = "textOfDate";
		date = GameSystem::getInstance()->getDataValue(date);

		auto dataDate = Label::createWithSystemFont(date, "����", 20);
		dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		dataDate->setPosition(160,65);
		stageLayer->addChild(dataDate);

		/*��ʾ�浵��ע*/
		//��ʵ��

	}
	else
	{
		/*��ʾ�浵���*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		stageLayer->addChild(dataNumber);
		*/

		/*��ʾ�浵��ͼ*/
		auto dataImage = Sprite::create("/ui/saveload/pic_bg.png");
		dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		dataImage->setPosition(15,101);
		stageLayer->addChild(dataImage);

		/*��ʾ�浵����*/
		auto dataDate = Label::createWithSystemFont("-/-/- --:--","����",20);
		dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		dataDate->setPosition(170, 65);
		stageLayer->addChild(dataDate);

		/*��ʾ�浵��ע*/
		//��ʵ��
	}

	this->setTouchEnabled(true);

	auto touchImage = Sprite::create("/ui/saveload/selected_bg.png");
	touchImage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	touchImage->setVisible(false);
	stageLayer->addChild(touchImage);

	auto eventTouch = EventListenerTouchOneByOne::create();

	eventTouch->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//�������ָ��
		{
			touchImage->setVisible(true);
			return true;
		}
		return false;
	};

	eventTouch->onTouchEnded = [=](Touch *t, Event *e)
	{
		touchImage->setVisible(false);
		if (stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//�������ָ��
		{
			
		}
		else
		{
			
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventTouch, this);

	this->addChild(stageLayer);
}

SaveData::~SaveData()
{
}

SaveData* SaveData::create(int i)
{
	auto tmpSavedata = new SaveData(i);
	return tmpSavedata;
}
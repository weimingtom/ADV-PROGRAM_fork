#include "SaveData.h"
#include "GameSystem.h"

#define NO_DATA_IMAGE ""

SaveData::SaveData(int number, std::string imageFile, std::string text, std::string date)
{
	/*¼ÓÔØ´æµµ°´Å¥±³¾°*/
	
	/*¼ÓÔØ´æµµ±àºÅ*/
	
	/*¼ÓÔØ´æµµ½ØÍ¼*/

	/*¼ÓÔØ´æµµĞÅÏ¢*/

	/*¼ÓÔØ±¸×¢ĞÅÏ¢*/
}

SaveData::SaveData(int number)
{
	/*¼ÓÔØ°´Å¥µ×²ã*/
	/*
	auto stageLayer = Layer::create();
	stageLayer->setContentSize(Size(400,110));
	*/

	auto stageLayer = Sprite::create("/ui/saveload/selected_bg.png");


	if (GameSystem::getInstance()->getSavedata(number))
	{
		/*ÏÔÊ¾´æµµĞòºÅ*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		stageLayer->addChild(dataNumber);
		*/

		/*ÏÔÊ¾´æµµ½ØÍ¼*/
		std::string imageFile = "imageOfSavedata";
		imageFile = GameSystem::getInstance()->getDataValue(imageFile);

		auto dataImage = Sprite::create(imageFile);
		dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		dataImage->setPosition(19, 99);
		stageLayer->addChild(dataImage);

		/*ÏÔÊ¾´æµµĞÅÏ¢*/
		std::string text = "textOfSavedata";
		text = GameSystem::getInstance()->getDataValue(text);

		auto dataText = Label::createWithSystemFont(text, "ºÚÌå", 20);
		dataText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		dataText->setPosition(160,35);
		stageLayer->addChild(dataText);

		/*ÏÔÊ¾´æµµÈÕÆÚ*/
		std::string date = "textOfDate";
		date = GameSystem::getInstance()->getDataValue(date);

		auto dataDate = Label::createWithSystemFont(date, "ºÚÌå", 20);
		dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		dataDate->setPosition(160,65);
		stageLayer->addChild(dataDate);

		/*ÏÔÊ¾´æµµ±¸×¢*/
		//´ıÊµÏÖ

	}
	else
	{
		/*ÏÔÊ¾´æµµĞòºÅ*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		stageLayer->addChild(dataNumber);
		*/

		/*ÏÔÊ¾´æµµ½ØÍ¼*/
		auto dataImage = Sprite::create("/ui/saveload/pic_bg.png");
		dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		dataImage->setPosition(15,101);
		stageLayer->addChild(dataImage);

		/*ÏÔÊ¾´æµµÈÕÆÚ*/
		auto dataDate = Label::createWithSystemFont("-/-/- --:--","ºÚÌå",20);
		dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		dataDate->setPosition(170, 65);
		stageLayer->addChild(dataDate);

		/*ÏÔÊ¾´æµµ±¸×¢*/
		//´ıÊµÏÖ
	}


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
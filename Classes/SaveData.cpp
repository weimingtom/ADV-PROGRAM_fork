#include "SaveData.h"
#include "GameSystem.h"

#define NO_DATA_IMAGE ""

SaveData::SaveData(int number, std::string imageFile, std::string text, std::string date)
{
	/*加载存档按钮背景*/
	
	/*加载存档编号*/
	
	/*加载存档截图*/

	/*加载存档信息*/

	/*加载备注信息*/
}

SaveData::SaveData(int i)
	: _dataImage(nullptr)
	, _dataDate(nullptr)
	, _dataText(nullptr)
{
	/*加载按钮底层*/
	/*
	auto stageLayer = Layer::create();
	_stageLayer->setContentSize(Size(400,110));
	_stageLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	*/
	_stageLayer = Sprite::create("/ui/saveload/noselected_bg.png");
	
	_number = i;

	updataData();

	onTouchEnded = [=](int i){};
	//this->setTouchEnabled(true);

	auto touchImage = Sprite::create("/ui/saveload/selected_bg.png");
	touchImage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	touchImage->setVisible(false);
	_stageLayer->addChild(touchImage);

	auto eventTouch = EventListenerTouchOneByOne::create();

	eventTouch->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (_stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//如果碰到指针
		{
			touchImage->setVisible(true);
			return true;
		}
		return false;
	};

	eventTouch->onTouchEnded = [=](Touch *t, Event *e)
	{
		touchImage->setVisible(false);
		if (_stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//如果碰到指针
		{
			onTouchEnded(_number);
			log("Wow!");
		}
		else
		{
			
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventTouch, this);

	this->addChild(_stageLayer);
}

SaveData::~SaveData()
{
}

SaveData* SaveData::create(int i)
{
	auto tmpSavedata = new SaveData(i);
	return tmpSavedata;
}

void SaveData::updataData()
{
	auto savedata = GameSystem::getInstance()->getGameSavedata(_number);
	bool isNeedReloadImageFile = false;
	if (_dataImage)
	{
		_dataImage->removeFromParent();
		isNeedReloadImageFile = true;
	}
	if (_dataDate) _dataDate->removeFromParent();
	if (_dataText) _dataText->removeFromParent();
	if (savedata)
	{
		/*显示存档序号*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		_stageLayer->addChild(dataNumber);
		*/

		/*显示存档截图*/

		std::string imageFile = savedata->imageFile;
		if (isNeedReloadImageFile)
		{
			Director::getInstance()->getTextureCache()->reloadTexture(imageFile);
			_dataImage = Sprite::createWithTexture(GameSystem::getInstance()->getScreenShoot()->getSprite()->getTexture());
			_dataImage->setScale(1, -1);
		}
		else
			_dataImage = Sprite::create(imageFile);
		if (_dataImage)
		{
			
			//_dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			_dataImage->setPosition(80, 55);
			_stageLayer->addChild(_dataImage);
		}

		/*显示存档信息*/
		std::string text = savedata->text;

		_dataText = Label::createWithSystemFont(text, "黑体", 20);
		_dataText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_dataText->setPosition(160, 35);
		_stageLayer->addChild(_dataText);

		/*显示存档日期*/
		std::string date = savedata->date;

		_dataDate = Label::createWithSystemFont(date, "黑体", 20);
		_dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_dataDate->setPosition(160, 65);
		_stageLayer->addChild(_dataDate);

		/*显示存档备注*/
		//待实现

	}
	else
	{
		/*显示存档序号*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		_stageLayer->addChild(dataNumber);
		*/

		/*显示存档截图*/
		_dataImage = Sprite::create("/ui/saveload/pic_bg.png");
		_dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		_dataImage->setPosition(15, 101);
		_stageLayer->addChild(_dataImage);

		/*显示存档日期*/
		_dataDate = Label::createWithSystemFont("-/-/- --:--", "黑体", 20);
		_dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_dataDate->setPosition(170, 65);
		_stageLayer->addChild(_dataDate);

		/*显示存档备注*/
		//待实现
	}
}

Sprite* SaveData::getStageLayer()
{
	//log("data Number = %d", _number);
	return _stageLayer;
}
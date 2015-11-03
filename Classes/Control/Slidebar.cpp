#include "Slidebar.h"


Slidebar::Slidebar(Sprite* backgroundSprite, Sprite* pointSprite)
{
	_background = backgroundSprite;
	this->addChild(_background);
	_point = pointSprite;
	this->addChild(_point);
	_pointPositionX = _point->getPositionX();
	_maxWidth = (_background->getContentSize().width - _point->getContentSize().width) / 2 ;
	_maxValue = 100;
	_minValue = 0;
	_targetValue = nullptr;
	log("Slidebar Done 1");
    _controlEvent = createControlEvent();
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_controlEvent, this);
}


Slidebar::~Slidebar()
{
}

Slidebar* Slidebar::createSlidebar(std::string backgroundFile, std::string pointFile)
{
	auto tmpBackgroundSprite = Sprite::create(backgroundFile);
	auto tmpPointSprite = Sprite::create(pointFile);
	if (tmpBackgroundSprite && tmpPointSprite)
	{
		auto tmpSlidebar = new Slidebar(tmpBackgroundSprite, tmpPointSprite);
		return tmpSlidebar;
	}
	else
	{
		if (!tmpBackgroundSprite) log("Sliderbar background file (%s) not found.", backgroundFile.c_str());
		if (!tmpPointSprite) log("Sliderbar point file (%s) not found.", pointFile.c_str());
		return nullptr;
	}
}

EventListenerTouchOneByOne* Slidebar::createControlEvent()
{
    auto et = EventListenerTouchOneByOne::create();
	
    et->onTouchBegan = [=](Touch *t, Event *e)
    {
		//log("Touch began.");
		if (_point->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//�������ָ��
		{
			//log("Touch!");
			return true;
		}
		else
		{
			if (_background->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))
			{
				float setP = this->convertTouchToNodeSpace(t).x;	//��ʱ��
				if (setP < _background->getPositionX() - _maxWidth)
					setP = _background->getPositionX() - _maxWidth;
				if (setP > _background->getPositionX() + _maxWidth)
					setP = _background->getPositionX() + _maxWidth;
				_point->setPositionX(setP);
				_pointPositionX = _point->getPositionX();
				return true;
			}
			//log("Not in touch!");
			return false;
		}
	};
	
    et->onTouchMoved = [=](Touch *t, Event *e)
    {
		float xOff = t->getLocation().x - t->getStartLocation().x;
		float LLimit = _background->getPositionX() - _pointPositionX - _maxWidth;
		float RLimit = _background->getPositionX() - _pointPositionX + _maxWidth;

		if (xOff < LLimit) xOff = LLimit;
		if (xOff > RLimit) xOff = RLimit;
		
		_point->setPositionX(_pointPositionX + xOff);
	};
	
    et->onTouchEnded = [=](Touch *t, Event *e)
    {
		//����ָ��λ��
		_pointPositionX = _point->getPositionX();
		//�ı�ı���
		float change = (_pointPositionX - (_background->getPositionX() - _maxWidth)) / (_maxWidth * 2);
		if (_targetValue)
		{
			*_targetValue = *_targetValue * change;
		}
		log("Target Value = %f", change
			);
	};
    
    return et;
}

void Slidebar::setMaxWidth(float value)
{
	_maxWidth = value;
}
#include "EasyButton.h"


EasyButton::EasyButton(Sprite* _normalSprite, Sprite* _touchSprite, Sprite* _selectedSprite)
{
	_normal = _normalSprite;
	this->addChild(_normal);
	_touch = _touchSprite;
	if (_touch)
	{
		this->addChild(_touch);
		_touch->setVisible(false);
	}
	_selected = _selectedSprite;
	if (_selected)
	{
		this->addChild(_selected);
		_selected->setVisible(false);
	}
	_eventTouch = EventListenerTouchOneByOne::create();
	_eventTouch->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (_normal->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//如果碰到指针
		{
			onTouchBegan(t, e);
			return true;
		}
		return false;
	};
	_eventTouch->onTouchMoved = [=](Touch *t, Event *e)
	{
		//onTouchMoved(t, e);
	};
	_eventTouch->onTouchEnded = [=](Touch *t, Event *e)
	{if (_normal->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//如果碰到指针
	{
		onTouchEnded(t, e, true);
	}
	else
	{
		onTouchEnded(t, e, false);
	}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_eventTouch, this);
	touchEvent = [=](){};
	touchEventWithInt = [=](){};
}


EasyButton::~EasyButton()
{
}

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile)
{
	auto normalSprite = Sprite::create(_normalFile);
	//Sprite* touchSprite = nullptr;
	//Sprite* selectSprite = nullptr;
	return new EasyButton(normalSprite, nullptr, nullptr);
};

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile, const std::string &_touchFile)
{
	auto normalSprite = Sprite::create(_normalFile);
	auto touchSprite = Sprite::create(_touchFile);
	//Sprite* selectSprite = nullptr;
	return new EasyButton(normalSprite, touchSprite, nullptr);
};

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile, const std::string &_touchFile, const std::string &_selectedFile)
{
	auto normalSprite = Sprite::create(_normalFile);
	auto touchSprite = Sprite::create(_touchFile);
	auto selectSprite = Sprite::create(_selectedFile);
	return new EasyButton(normalSprite, touchSprite, selectSprite);
};

void EasyButton::onTouchBegan(Touch *t, Event *e)
{
	if (_selected)
	{
		_normal->setVisible(false);
		_selected->setVisible(true);
	}
}

void EasyButton::onTouchEnded(Touch *t, Event *e, bool flag)
{
	if (_selected)
	{
		_normal->setVisible(true);
		_selected->setVisible(false);
	}
	if (flag)
	{
		touchEvent();
		touchEventWithInt;
	}
}
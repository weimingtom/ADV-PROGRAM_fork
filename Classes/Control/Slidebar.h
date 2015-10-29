#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Slidebar : public Node 
{
	Sprite* _background;
	Sprite* _point;
	int _maxValue;
	int _minValue;
	int* _targetValue;
	EventListenerTouchOneByOne* _controlEvent;
public:
	Slidebar(Sprite* backgroundSprite, Sprite* pointSprite);
	~Slidebar();
	static Slidebar* createSlidebar(std::string backgroundFile, std::string pointFile);
	void setLinkValue(int &value);
	void setMaxValue(int value);
	void setMinValue(int value);
	void valueChange();
	EventListenerTouchOneByOne* createControlEvent();	//建立控制事件
};


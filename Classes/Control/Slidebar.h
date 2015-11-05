#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Slidebar : public Node 
{
	Sprite* _background;
	Sprite* _point;
	float _maxValue;
	float _minValue;
	float* _targetValue;
	EventListenerTouchOneByOne* _controlEvent;
	float _pointPositionX;
	float _maxWidth;
	float _change;	//滑动条改变的倍率
	float _floatValue;	//浮点参数，被改变的值
public:
	Slidebar(Sprite* backgroundSprite, Sprite* pointSprite);
	~Slidebar();
	static Slidebar* createSlidebar(std::string backgroundFile, std::string pointFile);
	void setLinkValue(int &value);
	void setMaxValue(float value);
	void setMinValue(float value);
	void valueChange();
	EventListenerTouchOneByOne* createControlEvent();	//建立控制事件
	void setMaxWidth(float value);//设置滑块最大移动范围（半径）
	void setTargetValue(float *value);
	void changeTargetValue(float change);
	float getChange();	//获取滑动条改变的倍率
	void setSlidebar();	//自动设置滑块位置
	void setFloat(float value);	
	float getFloat();

	std::function<void()> touchEvent;	//触碰事件
	std::function<void()> moveEvent;	//移动事件
};


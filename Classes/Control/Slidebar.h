#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Slidebar : public Node 
{
	Sprite* _background;
	Sprite* _point;
	int _maxValue;
	int _minValue;
	float* _targetValue;
	EventListenerTouchOneByOne* _controlEvent;
	float _pointPositionX;
	float _maxWidth;
public:
	Slidebar(Sprite* backgroundSprite, Sprite* pointSprite);
	~Slidebar();
	static Slidebar* createSlidebar(std::string backgroundFile, std::string pointFile);
	void setLinkValue(int &value);
	void setMaxValue(int value);
	void setMinValue(int value);
	void valueChange();
	EventListenerTouchOneByOne* createControlEvent();	//���������¼�
	void setMaxWidth(float value);//���û�������ƶ���Χ���뾶��
	void setTargetValue(float *value);
	void changeTargetValue(float change);
};


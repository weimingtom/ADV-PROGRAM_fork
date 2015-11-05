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
	float _change;	//�������ı�ı���
	float _floatValue;	//������������ı��ֵ
public:
	Slidebar(Sprite* backgroundSprite, Sprite* pointSprite);
	~Slidebar();
	static Slidebar* createSlidebar(std::string backgroundFile, std::string pointFile);
	void setLinkValue(int &value);
	void setMaxValue(float value);
	void setMinValue(float value);
	void valueChange();
	EventListenerTouchOneByOne* createControlEvent();	//���������¼�
	void setMaxWidth(float value);//���û�������ƶ���Χ���뾶��
	void setTargetValue(float *value);
	void changeTargetValue(float change);
	float getChange();	//��ȡ�������ı�ı���
	void setSlidebar();	//�Զ����û���λ��
	void setFloat(float value);	
	float getFloat();

	std::function<void()> touchEvent;	//�����¼�
	std::function<void()> moveEvent;	//�ƶ��¼�
};


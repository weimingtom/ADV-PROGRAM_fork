#pragma once
#include "cocos2d.h"
#include "EasyButton.h"

USING_NS_CC;

class RadioButton : public Node
{
	std::vector<EasyButton*>* _radios;	//单选按钮组
	int _selected;	//当前选中的按钮下标
public:
	RadioButton();
	~RadioButton();
	static RadioButton* createRadioButton(EasyButton* i, ...);
	void touchEvent(int i);
	//void touchEvent();	//测试
};


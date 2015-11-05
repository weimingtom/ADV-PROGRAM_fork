#pragma once
#include "cocos2d.h"
#include "EasyButton.h"

USING_NS_CC;

class RadioButton : public Node
{
	std::vector<EasyButton*>* _radios;	//单选按钮组
	int _selectedNumber;	//当前选中的按钮下标
	int _tmpSelectedNumber;	//临时
	EasyButton* _selectedButton;	//当前被选中的按钮
	EasyButton* _tmpSelectedButton;	//临时储存被选中的按钮
	EventListenerTouchOneByOne* _eventTouch;	//触碰事件
public:
	RadioButton();
	~RadioButton();
	static RadioButton* createRadioButton(EasyButton* i, ...);
	std::function<void()> touchEvent;

	void onTouchBegan(Touch *t, Event *e);
	void onTouchEnded(Touch *t, Event *e, bool flag);

	int getSelectedNumber();	//返回选择按钮下标
	void setSelectedNumber(int selectedNumber);	//设置默认被选中的按钮
};


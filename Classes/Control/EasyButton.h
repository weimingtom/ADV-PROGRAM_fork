#pragma once
#include "cocos2d.h"

USING_NS_CC;
/*
这是简化版的Button，为了配合单选按钮组而设计的按钮。
*/
class EasyButton : public Node
{
	Sprite* _normal;	//普通状态的图片
	Sprite* _touch;		//触碰状态的图片
	Sprite* _selected;	//选择状态的图片
	EventListenerTouchOneByOne* _eventTouch;	//触碰事件
public:
	EasyButton(Sprite* _normalSprite, Sprite* _touchSprite, Sprite* _selectedSprite);
	~EasyButton();
	static EasyButton* createEasyButton(const std::string &_normalFile);
	static EasyButton* createEasyButton(const std::string &_normalFile, const std::string &_touchFile);
	static EasyButton* createEasyButton(const std::string &_normalFile, const std::string &_touchFile, const std::string &_selectedFile);

	void onTouchBegan(Touch *t, Event *e);
	void onTouchMoved(Touch *t, Event *e);
	void onTouchEnded(Touch *t, Event *e, bool flag);

	std::function<void()> touchEvent;	//触碰事件方法指针
	std::function<void(int i)> touchEventWithInt;	//带int参数的触碰事件方法指针
};


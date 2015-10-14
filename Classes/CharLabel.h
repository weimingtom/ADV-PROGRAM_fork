#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CharLabel:public Node
{
	Label* _charLabel;	//新生成的文字
	int _pos;	//当前显示的文字位置
	float _defaultDelayTime;	//默认显示文字时间
	float _fadeTime;	//文字fadein的时间
	int _defaultFontSize;	//默认文字大小
	std::string _text;	//要显示的字符串

	Color3B _defaultFontColor;

	//下次显示文字的位置
	float _lineHeight;	//文字行高
	float _x;	//显示位置坐标X
	float _y;	//显示位置坐标Y

	void showNextChar();	//显示下一个文字

	std::function<void()> _showFinishCallback;	//显示完成后的回调
public:
	CharLabel();
	~CharLabel();

	static CharLabel* create(std::string text, int fontSize = 24, std::function<void()> callback = nullptr);	//创建方法
	bool init(std::string &text, int fontSize);	//初始化，text 显示的文本，fontSize 文本大小

	/*
	设置要显示的字符串
	会直接替换当前字符串，也可以修改为动画消失
	*/
	void setString(std::string &text);

	/*
	瞬间显示字符串
	*/
	void finishShow();

	/*
	获取字符串下一个文字，针对UTF8
	*/
	static std::string getNextChar(std::string &src, int pos);

	/*
	显示全部完成时，调用的方法
	*/
	void setShowFinishCallback(std::function<void()> callback)
	{
		_showFinishCallback = callback;
	}

	/*
	设置文字颜色
	*/
	void setColor(Color3B color)
	{
		_defaultFontColor = color;
	}

};


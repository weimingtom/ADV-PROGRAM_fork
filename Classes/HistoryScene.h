#ifndef HISTORYSCENE_H
#define HISTORYSCENE_H
#include "cocos2d.h"
#include "History.hpp"
USING_NS_CC;

class HistoryMessage : public Node
{
	Label* _nameLabel;	//名字
	Label* _textLabel;	//文字
	Sprite* _voice;	//语音（暂留）
public:
	HistoryMessage(std::string text, std::string name, Color4B color);
	~HistoryMessage();
	static HistoryMessage* create(record* record);	//创建一条历史信息
};

class HistoryScene : public Layer
{
	int pointPositionY;
public:
	HistoryScene();
	~HistoryScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HistoryScene);

	void back();
};

#endif


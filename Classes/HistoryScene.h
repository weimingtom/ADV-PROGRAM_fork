#ifndef HISTORYSCENE_H
#define HISTORYSCENE_H
#include "cocos2d.h"
#include "History.hpp"
USING_NS_CC;

class HistoryMessage : public Node
{
	Label* _nameLabel;	//����
	Label* _textLabel;	//����
	Sprite* _voice;	//������������
public:
	HistoryMessage(std::string text, std::string name, Color4B color);
	~HistoryMessage();
	static HistoryMessage* create(record* record);	//����һ����ʷ��Ϣ
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


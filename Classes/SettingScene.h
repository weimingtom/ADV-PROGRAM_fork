#pragma once
#include "cocos2d.h"

USING_NS_CC;


class SettingScene : public Layer
{
public:
	SettingScene();
	~SettingScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);

	void back();	//·µ»Ø
};


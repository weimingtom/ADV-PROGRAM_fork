#pragma once
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class LoadScene : public Layer
{
	SaveData* dataButtons[8];
	EventListenerTouchOneByOne* eventTouch[8];
public:
	LoadScene();
	~LoadScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LoadScene);

	void back();	//·µ»Ø

	void load(int i);	//¶Áµµ
};


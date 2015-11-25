#pragma once
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class LoadScene : public Layer
{
public:
	LoadScene();
	~LoadScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LoadScene);

	void back();	//·µ»Ø

	void load(int i);	//¶Áµµ
};


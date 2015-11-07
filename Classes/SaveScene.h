#pragma once
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class SaveScene : public Layer
{
public:
	SaveScene();
	~SaveScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SaveScene);

	void back();	//·µ»Ø
};


#pragma once
#include "cocos2d.h"
#include "Control/RadioButton.h"
#include "Control/Slidebar.h"

USING_NS_CC;


class SettingScene : public Layer
{
	RadioButton* _testRadio;
	//Sliderbar
	Slidebar* _musicVolumeSlidebar;
public:
	SettingScene();
	~SettingScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);

	void back();	//∑µªÿ
	void test();	//≤‚ ‘∑Ω∑®
	void changeMusicVolume();
};


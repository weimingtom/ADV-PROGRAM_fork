#ifndef SETTING_SCENE_H
#define SETTING_SCENE_H

#include "cocos2d.h"
//#include "Control/RadioButton.h"
//#include "Control/Slidebar.h"

USING_NS_CC;

class RadioButton;

class Slidebar;

class SettingScene : public Layer
{
	//单选按钮组
	RadioButton* _testRadio;
	RadioButton* _isWindowRadio;	//窗口or全屏
	RadioButton* _isSkipReaded;		//是否跳过已阅
	//滑动条
	Slidebar* _musicVolumeSlidebar;	//音乐音量调节滑动条
	Slidebar* _soundVolumeSlidebar;	//音效音量调节滑动条
	Slidebar* _autoSpeedSlidebar;	//自动前进速度滑动条
	Slidebar* _skipSpeedSlidebar;	//快速前进速度滑动条
public:
	SettingScene();
	~SettingScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);

	void back();	//返回
	void test();	//测试方法
	void changeMusicVolume();
};

#endif

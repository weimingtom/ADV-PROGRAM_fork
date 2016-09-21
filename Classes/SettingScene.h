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
	RadioButton* _isWindow;	//窗口or全屏
    RadioButton* _isSkipAll;	//是否跳过已阅
	//滑动条
	Slidebar* _musicVolumeSlidebar;	//音乐音量调节滑动条
	Slidebar* _soundVolumeSlidebar;	//音效音量调节滑动条
	Slidebar* _autoSpeedSlidebar;	//自动前进速度滑动条
	Slidebar* _skipSpeedSlidebar;	//快速前进速度滑动条
    Slidebar* _textSpeedSlb;        //文本显示速度
public:
	SettingScene();
	~SettingScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);

	void back();	//返回
	void test();	//测试方法
	void changeMusicVolume();   //改变音乐音量
    void changeSoundVolume();   //改变音效音量
    void changeTextSpeed();     //改变文本显示速度
    void changeAutoSpeed();     //改变自动播放速度
    void changeIsSkipAll();     //改变是否跳过全部
};

#endif

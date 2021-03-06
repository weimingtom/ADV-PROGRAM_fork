#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"

#define MAX_CHARACTOR_NUMBER 5

class GameScene : public cocos2d::Layer
{
	cocos2d::Label* _label;//文本框的文本层
	//ScriptReader* _reader;	//脚本解析器

	Label* _nameLabel;	//姓名框
	CharLabel* _textLabel;	//对白框
	Sprite* _dialogWindow;	//文本框背景
	Layer* _backgroundLayer;	//背景层
	Sprite* _backgroundSprite;	//背景图片
	Layer* _charactorsLayer;	//立绘层
	Layer* _selectLayer;	//选项层

	Charactor* _chars[MAX_CHARACTOR_NUMBER];	//储存当前立绘资料
	Charactor* _emptyChar;	//空角色
	int _charNumber;	//储存立绘数量

	bool _isPlayingMusic;	//音乐播放状态

	std::string _backgroundKey;	//当前背景
	std::string _backgroundMusicKey;	//当前背景音乐
	std::string _soundKey;	//当前音效
	std::string _currentText;	//当前文本
	std::string _currentName;	//当前姓名
	std::map<std::string, std::string> _currentOptions;	//当前选项
	int _optionsNumber;	//当前选项数量

public:
	GameScene();
	~GameScene();
	
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float dt);

	void updateLabel(std::string text);

	void showName(std::string &name);	//姓名框

	void showText(std::string &text);	//显示文本

	void showClickSign();	//点击继续图标

	void screenClicked();	//屏幕点击事件，除了按钮、对话框

	void dialogClicked();	//显示下一句对话

	void changeBackground(std::string &key);	//切换场景

	void playBackgroundMusic(std::string &key);	//播放音乐
	void stopBackgroundMusic();						//停止音乐
	void scheduleVolumeFadeIn();	//音乐淡入
	void scheduleVolumeFadeOut();	//音乐淡出

	void playSound(std::string &file);	//播放音效
	void stopSound();					//停止音效

	void startAutoPlay();	//开始自动前进
	void stopAutoPlay();	//停止自动前进
	void autoPlay(float dt);	//自动前进

	void displayCharator(std::string cName,std::string face);
	void unDisplayCharator(std::string cName);

	void createGameDate();

	void showSaveScene();	//进入存档界面
	void showLoadScene();	//进入读档界面
	void showHistoryScene();	//进入历史记录界面

	void ScreenShoot();	//截屏

	void clear();	//清楚屏幕的所有东西
	void reloadScene();	//重载场景，通常读档用

	void showSelect(std::map<std::string, std::string> &options);	//显示选项

};


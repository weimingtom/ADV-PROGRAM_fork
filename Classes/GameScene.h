#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"


class GameScene : public cocos2d::Layer
{
	cocos2d::Label* _label;//文本框的文本层
	ScriptReader* _reader;	//脚本解析器

	Label* _nameLabel;	//姓名框
	CharLabel* _textLabel;	//对白框
	Sprite* _dialogWindow;	//文本框背景
	Layer* _backgroundLayer;	//背景层
	Sprite* _backgroundSprite;	//背景图片
	Layer* _charactorsLayer;	//立绘层

	Charactor* _chars[5];	//储存立绘资料
	int _charNumber;	//储存立绘数量

	bool _isPlayingMusic;	//音乐播放状态
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

	void changeBackground(Sprite &background);	//切换场景

	void playBackgroundMusic(std::string &file);	//播放音乐
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
};


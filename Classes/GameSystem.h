#pragma once
#include "cocos2d.h"

#define SYSTEMVOLUME "SystemVolume"
#define MUSICVOLUME "MusicVolume"
#define SOUNDVOLUME "SoundVolume"
#define TEXTSPEED "TextSpeed"
#define AUTOSPEED "AutoSpeed"

class GameSystem
{
	static GameSystem* _instance;	//实例
	
	//音量
	float _systemVolume;	//总音量
	float _musicVolume;	//音乐音量
	float _soundVolume;	//音效音量

	//演出相关
	float _textSpeed;		//文字速度
	float _autoSpeed;		//自动速度

	//系统参数
	
	std::map<std::string, int>* _savedata;		//游戏变量

public:
	GameSystem();
	~GameSystem();
	static GameSystem* getInstance();
	void destoryInstance();
	void setDefault();

	void setSystemVolume(float value);
	void setMusicVolume(float value);
	void setSoundVolume(float value);
	void setTextSpeed(float value);
	void setAutoSpeed(float value);

	float getSystemVolume();
	float getMusicVolume();
	float getSoundVolume();
	float getTextSpeed();
	float getAutoSpeed();

	void setDataValue(std::string &key, int value);
	int getDataValue(std::string &key);
	void setData(std::map<std::string, int> *map = nullptr);

};


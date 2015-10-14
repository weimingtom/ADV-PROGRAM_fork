#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define BMM BackgroundMusicManager::getInstance()

class BackgroundMusicManager
{
	BackgroundMusicManager();
	~BackgroundMusicManager();
	static BackgroundMusicManager* _instance;

	std::map<std::string, std::string> *_pool;	//配置文件列表。<音乐key，音乐文件>

	std::string defaultBackgroundMusic;	//脚本指定的音乐未定义则使用默认音乐
public:
	static BackgroundMusicManager* getInstance();
	static void destoryInstance();

	std::string getBackgroundMusic(std::string key);	//根据Key值获取音乐

	void addBackgroundMusic(std::string key, std::string bgm);	//存储音乐信息
};
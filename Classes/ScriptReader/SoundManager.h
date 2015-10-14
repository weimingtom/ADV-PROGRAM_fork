#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define SM SoundManager::getInstance()

class SoundManager
{
	SoundManager();
	~SoundManager();
	static SoundManager* _instance;

	std::map<std::string, std::string> *_pool;	//配置文件列表。<音乐key，音乐文件>

	std::string defaultSound;	//脚本指定的音乐未定义则使用默认音乐
public:
	static SoundManager* getInstance();
	static void destoryInstance();

	std::string getSound(std::string key);	//根据Key值获取音乐

	void addSound(std::string key, std::string sound);	//存储音乐信息
};
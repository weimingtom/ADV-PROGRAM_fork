#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include "cocos2d.h"

USING_NS_CC;

#define BM BackgroundManager::getInstance()

class BackgroundManager
{
	BackgroundManager();
	~BackgroundManager();
	static BackgroundManager* _instance;	//背景管理器实例

	std::map<std::string, std::string> *_pool;	//配置文件列表。<场景key，场景文件>

	std::string defaultBackground;	//脚本出现的角色未定义则使用默认场景
public:
	static BackgroundManager* getInstance();	//获取背景管理器实例
	static void destoryInstance();

	std::string getBackground(std::string key);	//根据Key值获取场景

	void addBackground(std::string key, std::string background);	//存储场景信息
};

#endif


#include "BackgroundManager.h"

//脚本文件路径
#define BGLISTPATH "/bgimage/bgList.txt"

BackgroundManager* BackgroundManager::_instance = nullptr;

BackgroundManager::BackgroundManager()
	:_pool(nullptr)
{
	_pool = new std::map<std::string, std::string>();	//创建容器

	defaultBackground = "";	//设定默认的背景为空地址

	std::string ss = FileUtils::getInstance()->getStringFromFile(BGLISTPATH);	//读取文件

	int sPos = 0;	//行头
	int ePos = 0;	//行尾
	//预先读取一行不处理，解决BOM头
	ePos = ss.find('\n', sPos);
	sPos = ePos + 1;

	/*开始处理*/
	while (1)
	{
		std::string key;	//临时储存场景名
		std::string background;	//储存背景
		std::string temp;	//临时储存一行信息

		/*读取一行信息*/
		ePos = ss.find('\n', sPos);
		temp = ss.substr(sPos, ePos - sPos - 1);
		if (temp.compare("") == 0)	//如果是空的就是文件尾了
		{
			break;
		}
		sPos = ePos + 1;

		/*提取出背景文件名后自动补全路径*/
		int tempPos = temp.find_first_of(',', 0);
		key = temp.substr(0, tempPos);
		background = temp.substr(tempPos + 1, temp.length() - tempPos - 1);
		background = "/bgimage/" + background;

		//log("bgkey = %s , backgroundPath = %s", key.c_str(), background.c_str());

		/*添加进场景容器*/
		addBackground(key, background);
		log("SCB> addBackground[%s]", key.c_str());
	}
}


BackgroundManager::~BackgroundManager()
{
	if (_pool)
	{
		_pool->clear();
		delete _pool;
		_pool = nullptr;
	}
}


void BackgroundManager::addBackground(std::string key, std::string background)
{
	_pool->insert(std::pair<std::string, std::string>(key,background));
}

std::string BackgroundManager::getBackground(std::string key)
{
	auto result = _pool->find(key);
	if (result != _pool->end())
	{
		return result->second;
	}
	else
	{
		log("BM> Unfind &s", key);
		defaultBackground = "/bgimage/Black.png";
		return defaultBackground;
	}
}

BackgroundManager* BackgroundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new BackgroundManager();
	}
	return _instance;
}

void BackgroundManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}
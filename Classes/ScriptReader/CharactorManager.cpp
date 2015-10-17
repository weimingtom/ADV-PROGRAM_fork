#include "CharactorManager.h"
#define charactorPath "/charactor/charactorList.txt"

CharactorManager* CharactorManager::_instance = nullptr;

CharactorManager::CharactorManager()
	:_pool(nullptr)
	, defaultCharactor(nullptr)
{
	_pool = new std::map<std::string, Charactor*>();

	defaultCharactor = new Charactor();

	//Load datas

	std::string ss = FileUtils::getInstance()->getStringFromFile(charactorPath);

	int sPos = 0;
	int ePos = 0;
	//预先读取一行不处理，解决BOM头
	ePos = ss.find('\n', sPos);
	sPos = ePos + 1;
	
	while (1)
	{
		auto tempCharactor = new Charactor();
		std::string key;
		std::string name;
		ePos = ss.find('\n', sPos);
		key = ss.substr(sPos, ePos - sPos - 1);
		if (key.compare("") == 0)
		{
			break;
		}
		sPos = ePos + 1;
		ePos = ss.find('\n', sPos);
		name = ss.substr(sPos, ePos - sPos - 1);
		tempCharactor->name = name;
		sPos = ePos + 1;
		tempCharactor->fgList = new std::map<std::string, char*>();
		while (1)
		{
			std::string temp;
			ePos = ss.find('\n', sPos);
			temp = ss.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			if (temp.compare("") == 0) break;
			std::string face;
			std::string facePath;
			int tempPos = temp.find_first_of(',', 0);
			face = temp.substr(0, tempPos);
			facePath = temp.substr(tempPos + 1, temp.length() - tempPos - 1);
			facePath = "/charactor/" + facePath + ".png";
			char* tmpfacePath = new char;
			facePath.copy(tmpfacePath,facePath.length(),0);
			*(tmpfacePath + facePath.length()) = '\0';
			tempCharactor->fgList->insert(std::pair<std::string, char*>(face, tmpfacePath));
		}

		/*
		//check list
		for (auto i = tempCharactor->fgList->begin(); i != tempCharactor->fgList->end(); i++)
		{
			log("%s , %s", i->first.c_str(), i->second);
		}
		*/

		addCharactor(key, tempCharactor);
		log("CM> addCharactor[%s]", tempCharactor->name.c_str());
	}
	


	auto c1 = new Charactor();
	c1->name = "P1";
	c1->color = Color3B::BLACK;

	std::string key = "c1";
	addCharactor(key, c1);

	//auto c2 = new Charactor();
	c1 = new Charactor();
	c1->name = "Maid";

	key = "c2";
	addCharactor(key, c1);
}


CharactorManager::~CharactorManager()
{
	if (_pool)
	{
		for (auto i = _pool->begin(); i != _pool->end(); i++)
		{
			delete i->second;
		}
		_pool->clear();
		delete _pool;
		_pool = nullptr;
	}

	if (defaultCharactor)
	{
		delete defaultCharactor;
		defaultCharactor = nullptr;
	}
}

CharactorManager* CharactorManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new CharactorManager();
	}
	return _instance;
}

void CharactorManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

Charactor* CharactorManager::getCharactor(std::string &key)
{
	auto result = _pool->find(key);
	if (result != _pool->end())
	{
		return result->second;
	}
	else
	{
		defaultCharactor->name = "Undefind Charactor[" + key + "]";
		return defaultCharactor;
	}
}

void CharactorManager::addCharactor(std::string &key, Charactor* cha)
{
	_pool->insert(std::pair<std::string, Charactor*>(key, cha));
}



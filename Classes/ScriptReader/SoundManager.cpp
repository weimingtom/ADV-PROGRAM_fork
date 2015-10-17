#include "SoundManager.h"

#define SOUNDLISTPATH "/sound/soundList.txt"

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager()
	:_pool(nullptr)
{
	_pool = new std::map<std::string, std::string>();

	defaultSound = "";

	std::string ss = FileUtils::getInstance()->getStringFromFile(SOUNDLISTPATH);

	int sPos = 0;
	int ePos = 0;
	//预先读取一行不处理，解决BOM头
	ePos = ss.find('\n', sPos);
	sPos = ePos + 1;

	while (1)
	{
		std::string key;
		std::string sound;
		std::string temp;
		ePos = ss.find('\n', sPos);
		temp = ss.substr(sPos, ePos - sPos - 1);
		if (temp.compare("") == 0)
		{
			log("SM> Load Sound ending");
			break;
		}
		sPos = ePos + 1;

		int tempPos = temp.find_first_of(',', 0);
		key = temp.substr(0, tempPos);
		sound = temp.substr(tempPos + 1, temp.length() - tempPos - 1);
		sound = "/sound/" + sound + ".mp3";

		log("soundkey = %s , soundPath = %s", key.c_str(), sound.c_str());

		addSound(key, sound);
		log("SM> addSound[%s]", key.c_str());
	}
}


SoundManager::~SoundManager()
{
	if (_pool)
	{
		_pool->clear();
		delete _pool;
		_pool = nullptr;
	}
}


void SoundManager::addSound(std::string key, std::string sound)
{
	_pool->insert(std::pair<std::string, std::string>(key, sound));
}

std::string SoundManager::getSound(std::string key)
{
	auto result = _pool->find(key);
	if (result != _pool->end())
	{
		return result->second;
	}
	else
	{
		log("SM> Unfind &s", key);
		defaultSound = "";
		return defaultSound;
	}
}

SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SoundManager();
		//log("SM> instance starting...");
	}
	return _instance;
}

void SoundManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}
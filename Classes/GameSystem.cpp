#include "GameSystem.h"
#include "cocos2d\cocos\base\CCUserDefault.h"
#include <stdlib.h>

#define DEFAULT_SYSTEMVOLUME 1.0f
#define DEFAULT_MUSICVOLUME 1.0f
#define DEFAULT_SOUNDVOLUME 1.0f
#define DEFAULT_TEXTSPEED 1.0f
#define DEFAULT_AUTOSPEED 1.0f

#define ISINIT "isInitialization"	//初始化标记



GameSystem* GameSystem::_instance = nullptr;

GameSystem::GameSystem()
{
	if (!cocos2d::UserDefault::getInstance()->getBoolForKey(ISINIT))	//判断是否初始化过
	{
		setDefault();
	}
	_isNewGame = true;
	_savedata = new std::map<std::string, int>[100];
}


GameSystem::~GameSystem()
{
	delete _savedata;
	if (_gameSceneInfo) delete _gameSceneInfo;
}

GameSystem* GameSystem::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameSystem();
	}
	return _instance;
}

void GameSystem::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}
void GameSystem::setDefault()
{
	setSystemVolume(DEFAULT_SYSTEMVOLUME);
	setMusicVolume(DEFAULT_MUSICVOLUME);
	setSoundVolume(DEFAULT_SOUNDVOLUME);
	setTextSpeed(DEFAULT_TEXTSPEED);
	setAutoSpeed(DEFAULT_AUTOSPEED);
	cocos2d::UserDefault::getInstance()->setBoolForKey(ISINIT, true);
}

void GameSystem::setSystemVolume(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(SYSTEMVOLUME, value);
}

void GameSystem::setMusicVolume(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(MUSICVOLUME, value);
}

void GameSystem::setSoundVolume(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(SOUNDVOLUME, value);
}

void GameSystem::setTextSpeed(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(TEXTSPEED, value);
}

void GameSystem::setAutoSpeed(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(AUTOSPEED, value);
}



float GameSystem::getSystemVolume()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(SYSTEMVOLUME);
}

float GameSystem::getMusicVolume()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(MUSICVOLUME);
}

float GameSystem::getSoundVolume()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(SOUNDVOLUME);
}

float GameSystem::getTextSpeed()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(TEXTSPEED);
}

float GameSystem::getAutoSpeed()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(AUTOSPEED);
}

void GameSystem::setDataValue(std::string &key, int value)
{
	auto result = _savedata[0].find(key);
	if (result != _savedata[0].end())
	{
		result->second = value;
	}
	else
	{
		_savedata[0].insert(std::pair<std::string, int>(key, value));
	}
}

int GameSystem::getDataValue(std::string &key)
{
	auto result = _savedata[0].find(key);
	if (result != _savedata[0].end())
	{
		// cocos2d::log("GS> key = %s , value = %d", key.c_str(), result->second);
		return result->second;
	}
	else
	{
		return 0;
	}
}

void GameSystem::setData(std::map<std::string, int> *map)// = nullptr)
{
	if (map == nullptr)
	{
		if (!(_savedata[0].empty())) _savedata[0].clear();
	}
	else
	{
		_savedata[0] = *map;
	}
}

void GameSystem::setSavedata(int i, bool value)
{
	char* ch = new char[4];
	itoa(i, ch, 10);
	cocos2d::UserDefault::getInstance()->setBoolForKey(ch, value);
}

bool GameSystem::getSavedata(int i)
{
	char* ch = new char[4];
	itoa(i, ch, 10);
	return cocos2d::UserDefault::getInstance()->getBoolForKey(ch);
}

GameData* GameSystem::getGameSceneInfo()
{
	return _gameSceneInfo;
}

void GameSystem::setGameSceneInfo(GameData* gameData)
{
	_gameSceneInfo = gameData;
}

void GameSystem::setIsNewGame(bool value)
{
	_isNewGame = value;
}

bool GameSystem::getIsNewGame()
{
	return _isNewGame;
}

void GameSystem::saveGameSceneInfo(int i)
{
	setSavedata(i, true);
	/*将信息保存到savedata对应的file*/
	char path[] = "savedata\\savedata";
	char ch[2];
	sprintf(ch,"%d",i);
	char file[26];
	sprintf(file, "%s%s%s", path, ch, ".sav");
	cocos2d::log("Savedata file path = %s",file);
	FILE* savedata = fopen(file,"wb");
	if (savedata)
	{
		/*保存存档信息*/
		/*--储存截图路径*/
		/*--储存时间*/
		time_t t;
		time(&t);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", localtime((&t)));
		fwrite(tmp, sizeof(char), strlen(tmp), savedata);
		fputs("\r\n", savedata);
		/*保存当前对白*/
		fwrite(_gameSceneInfo->currentText.c_str(), sizeof(char), strlen(_gameSceneInfo->currentText.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前名字*/
		fwrite(_gameSceneInfo->currentName.c_str(), sizeof(char), strlen(_gameSceneInfo->currentName.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前背景key*/
		fwrite(_gameSceneInfo->backgroundKey.c_str(), sizeof(char), strlen(_gameSceneInfo->backgroundKey.c_str()), savedata);
		fputs("\r\n", savedata);	//换行
		/*保存当前立绘数量*/
		char cCharactorCount[2];
		sprintf(cCharactorCount, "%d", _gameSceneInfo->charactorCount);
		fwrite(cCharactorCount, sizeof(char), strlen(cCharactorCount), savedata);
		fputs("\r\n", savedata);
		/*保存当前立绘信息*/
		for (int j = 0; j < _gameSceneInfo->charactorCount; j++)
		{	/*保存角色key*/
			fwrite(_gameSceneInfo->fgCharactors[j].name.c_str(), sizeof(char), strlen(_gameSceneInfo->fgCharactors[j].name.c_str()), savedata);
			fputs("\r\n", savedata);
			/*保存角色表情*/
			fwrite(_gameSceneInfo->fgCharactors[j].face.c_str(), sizeof(char), strlen(_gameSceneInfo->fgCharactors[j].face.c_str()), savedata);
			fputs("\r\n", savedata);
			/*保存角色位置*/
			char num[2];
			sprintf(num, "%d", _gameSceneInfo->fgCharactors[j].number);
			fwrite(num, sizeof(char), strlen(num), savedata);
			fputs("\r\n", savedata);
		}
		/*保存当前BGM信息*/
		fwrite(_gameSceneInfo->bgmKey.c_str(), sizeof(char), strlen(_gameSceneInfo->bgmKey.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前sound信息*/
		fwrite(_gameSceneInfo->bgmKey.c_str(), sizeof(char), strlen(_gameSceneInfo->bgmKey.c_str()), savedata);
		fputs("\r\n", savedata);

		fclose(savedata);
	}
	else
	{
		cocos2d::log("savedata file error.");
	}
	savedata = NULL;
}
#include "GameSystem.h"
#include "base\CCUserDefault.h"
#include <stdlib.h>
#include "ScriptReader/ScriptReader.h"
#include "ScriptReader/CharactorManager.h"
#include "ScriptReader/BackgroundManager.h"
#include "ScriptReader/BackgroundMusicManager.h"


#define DEFAULT_SYSTEMVOLUME 1.0f
#define DEFAULT_MUSICVOLUME 1.0f
#define DEFAULT_SOUNDVOLUME 1.0f
#define DEFAULT_TEXTSPEED 1.0f
#define DEFAULT_AUTOSPEED 1.0f
#define DEFAULT_ISSKIPALL false
#define MAX_SAVEDATA_NUMBER 100

#define ISINIT "isInitialization"	//初始化标记



GameSystem* GameSystem::_instance = nullptr;

GameSystem::GameSystem()
{
	if (!cocos2d::UserDefault::getInstance()->getBoolForKey(ISINIT))	//判断是否初始化过
	{
		setDefault();
	}
	_isLoadSuccess = false;
	_savedata = new std::map<std::string, int>[100];    //为什么是100？我已经不记得了，大概当时想着可以存100个档案的变量，0作为当前游戏储存的变量吧。有空再改
	_gameSceneInfo = nullptr;
    
    //初始化各种数值
    
	//初始化存档列表
	_savedataList = new GameSaveData[MAX_SAVEDATA_NUMBER];
	createSavedata();
	initGameSavedataList();
	_gameScene = nullptr;
    
    //initialization Manager
    CharactorManager::getInstance();
    BackgroundManager::getInstance();
    BackgroundMusicManager::getInstance();
}


GameSystem::~GameSystem()
{
    if (_savedata)
	delete _savedata;
	if (_gameSceneInfo)
	{
		delete _gameSceneInfo;
		_gameSceneInfo = nullptr;
	}
	delete _savedataList;
    //if (_screenShoot) _screenShoot->release();
	if (_gameScene)
	{
		//delete _gameScene;
		_gameScene = nullptr;
	}
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
    setIsSkipAll(DEFAULT_ISSKIPALL);
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

void GameSystem::setHaveRead(const std::string &key, int value)
{
    cocos2d::UserDefault::getInstance()->setIntegerForKey(key.c_str(), value);
    cocos2d::UserDefault::sharedUserDefault()->flush();//为什么其它没加这句？因为其它没加这句也在正常运行，我就不加先了。
}

void GameSystem::setIsSkipAll(bool value)
{
    cocos2d::UserDefault::getInstance()->setBoolForKey(ISSKIPALL, value);
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

int GameSystem::getHaveRead(const std::string &key)
{
    return cocos2d::UserDefault::getInstance()->getIntegerForKey(key.c_str());
}

bool GameSystem::getIsSkipAll()
{
    return cocos2d::UserDefault::getInstance()->getBoolForKey(ISSKIPALL);
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
    //cocos2d::UserDefault::sharedUserDefault()->flush();
}

int GameSystem::getDataValue(std::string &key)
{
	auto result = _savedata[0].find(key);
    cocos2d::log("GS> key = %s", key.c_str());
	if (result != _savedata[0].end())
	{
		cocos2d::log("GS> key = %s , value = %d", key.c_str(), result->second);
		return result->second;
	}
	else
	{
		return 0;
	}
}

bool GameSystem::isDataValueExists(const std::string &key)
{
    auto result = _savedata[0].find(key);
    if (result != _savedata[0].end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string GameSystem::dataValueToString()
{
    std::string dataValueStr = "";
    for (auto it=_savedata[0].begin(); it!=_savedata[0].end(); ++it)
    {
        dataValueStr += it->first;
        dataValueStr += "=";
        char* ch = new char[6];
        //itoa(i, ch, 10);
        sprintf(ch, "%d", it->second);
        dataValueStr += ch;
        delete[] (ch);
        dataValueStr += ",";
    }
    return dataValueStr;
}

void GameSystem::stringToDataValue(const std::string &dataValueStr)
{
    //清空_savadata
    if (_savedata != nullptr)
    {
        delete [] _savedata;
    }
    _savedata = new std::map<std::string, int>[100];
    
    log("dataValueStr = %s", dataValueStr.c_str());
    
    //对字符串进行处理
    int sPos = 0;	//行头
    int ePos = 0;	//行尾
    std::string temp;	//临时储存一行信息
    while(sPos < dataValueStr.length())
    {
        /*读取每一个分割*/
        ePos = dataValueStr.find(',', sPos);
        temp = dataValueStr.substr(sPos, ePos - sPos);
        //对每一个分割进行处理
        std::string key;
        std::string value;
        log("temp = %s", temp.c_str());
        key = temp.substr(0, temp.find('=', 0));
        value = temp.substr(key.length()+1, temp.length() - (key.length()+1));
        log("key = %s, value = %s", key.c_str(), value.c_str());
        
        setDataValue(value, atoi(value.c_str()));
        
        sPos = ePos + 1;
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
	//itoa(i, ch, 10);
    sprintf(ch, "%d", i);
	cocos2d::UserDefault::getInstance()->setBoolForKey(ch, value);
}

bool GameSystem::getSavedata(int i)
{
	char* ch = new char[4];
	//itoa(i, ch, 10);
    sprintf(ch, "%d", i);
    delete[] (ch);
	return cocos2d::UserDefault::getInstance()->getBoolForKey(ch);
}

GameData* GameSystem::getGameSceneInfo()
{
	return _gameSceneInfo;
}

void GameSystem::setGameSceneInfo(GameData* gameData)
{
	if (_gameSceneInfo)
	{
		delete _gameSceneInfo;
		_gameSceneInfo = nullptr;
	}
	_gameSceneInfo = gameData;
}

void GameSystem::setIsLoadSuccess(bool value)
{
	_isLoadSuccess = value;
}

bool GameSystem::getIsLoadSuccess()
{
	return _isLoadSuccess;
}

void GameSystem::saveGameSceneInfo(int i)
{
	setSavedata(i, true);
	/*将信息保存到savedata对应的file*/
	const char * path = "savedata/savedata";
	char *ch = new char[3];
	sprintf(ch, "%d", i+1);
    cocos2d::log("ch = %s", ch);
    char *file = new char[500];
	sprintf(file, "%s%s%s.sav", FileUtils::getInstance()->getWritablePath().c_str(), path, ch);
    char *image = new char[100];
	sprintf(image, "%s%d.jpg", path, i+1);
	cocos2d::log("Savedata file path = %s",file);
	cocos2d::log("Savedata image path = %s", image);
	FILE* savedata = fopen(file,"wb");
	if (savedata)
	{
		/*保存存档信息*/
		/*--储存截图路径*/
		bool result = _screenShoot->saveToFile(image, false, [&](RenderTexture *r, const  std::string &s){ });
		if (result)
		{
			char tmp[100];
			//sprintf(tmp, "%s%s", FileUtils::getInstance()->getWritablePath().c_str(), image);
            //只保存图片的名字，不记录路径，因为在iOS中每一次启动进程WritablePath都是不一样的。
            sprintf(tmp, "%s", image);
			fwrite(tmp, sizeof(char), strlen(tmp), savedata);
		}
		fputs("\r\n", savedata);
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
		{	
			/*保存角色key*/
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
		//fwrite(_gameSceneInfo->bgmKey.c_str(), sizeof(char), strlen(_gameSceneInfo->bgmKey.c_str()), savedata);
		//fputs("\r\n", savedata);
		/*保存当前选项*/
		char num[2];
		sprintf(num, "%d", _gameSceneInfo->optionsNumber);
		fwrite(num, sizeof(char), strlen(num), savedata);
		fputs("\r\n", savedata);
		if (_gameSceneInfo->optionsNumber)
		{
			for (auto itr = _gameSceneInfo->options.begin(); itr != _gameSceneInfo->options.end(); itr++)
			{
				fwrite(itr->first.c_str(), sizeof(char), strlen(itr->first.c_str()), savedata);
				fputs("\r\n", savedata);
				fwrite(itr->second.c_str(), sizeof(char), strlen(itr->second.c_str()), savedata);
				fputs("\r\n", savedata);
			}
		}
        
		/*保存当前ScriptReader标签*/
		auto sign = ScriptReader::getInstance()->getCurrentSignName();
		fwrite(sign.c_str(), sizeof(char), strlen(sign.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前的CommandIndex*/
		auto commandIndex = ScriptReader::getInstance()->getCurrentCommandIndex();
		char sCommandIndex[4];
		sprintf(sCommandIndex, "%d", commandIndex);
		fwrite(sCommandIndex, sizeof(char), strlen(sCommandIndex), savedata);
		fputs("\r\n", savedata);
        /*保存当前的变量*/
        auto dataValueStr = dataValueToString();
        fwrite(dataValueStr.c_str(), sizeof(char), strlen(dataValueStr.c_str()), savedata);
        fputs("\r\n", savedata);
        
		fclose(savedata);
        
        cocos2d::log("savedata done");
		
	}
	else
	{
		cocos2d::log("savedata file error.");
	}
    delete[] ch;
    delete[] file;
    delete[] image;
	savedata = NULL;
 }

void GameSystem::initGameSavedataList()
{
	//记录cocos2d-x中CCFileUtils，对于没有找到文件是否弹出提示框的设置
	bool isNeedModifyPopupSetting = FileUtils::sharedFileUtils()->isPopupNotify();
	//如果有提示，就暂时关闭，因为这里的读取可能找不到该文件，因为该文件有可能还没有创建
	if (isNeedModifyPopupSetting)
	{
		FileUtils::sharedFileUtils()->setPopupNotify(false);
	}

	for (int i = 0; i < MAX_SAVEDATA_NUMBER; i++)
	{
		updateGameSavedata(i);
	}

	//如果以前设置找不到文件有提示，则改回原来的设置
	if (isNeedModifyPopupSetting)
	{
		FileUtils::sharedFileUtils()->setPopupNotify(true);
	}
}

GameSaveData* GameSystem::getGameSavedata(int i)
{
	if (_savedataList[i].date.compare("") == 0)
		return nullptr;
	else
		return &_savedataList[i];
}

void GameSystem::createSavedata()
{
	//绑定用户储存目录下
	std::string path = FileUtils::getInstance()->getWritablePath();
	//创建savedata文件夹
	path += "savedata";
	//log("path=%s", pathToSave.c_str());

/*
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *pDir = NULL;
	//打开该路径
	pDir = opendir(path.c_str());
	if (!pDir)
	{
		//创建该路径
		mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}
#else
	if ((GetFileAttributesA(path.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(path.c_str(), 0);
	}
#endif
*/
    if (!FileUtils::getInstance()->isDirectoryExist(path))
    {
        FileUtils::getInstance()->createDirectory(path);
        log("savedata created.");
    }
    else
    {
        log("savedata has created.");
    }
	
}

void GameSystem::setScreenShoot(RenderTexture* render)
{
	_screenShoot = render;
}

RenderTexture* GameSystem::getScreenShoot()
{
	return _screenShoot;
}

void GameSystem::updateGameSavedata(int i)
{
	char path[] = "savedata/savedata";
	char ch[4];
	sprintf(ch, "%d", i+1);
	char file[100];
	sprintf(file, "%s%s%s%s", FileUtils::getInstance()->getWritablePath().c_str(), path, ch, ".sav");

	std::string data = FileUtils::getInstance()->getStringFromFile(file);
	if (data.compare("") != 0)
	{
		int sPos = 0;	//行头
		int ePos = 0;	//行尾
		std::string temp;	//临时储存一行信息
		/*读取存档截图路径*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		Director::getInstance()->getTextureCache()->reloadTexture(FileUtils::getInstance()->getWritablePath() + temp);
		//cocos2d::log(temp.c_str());
		_savedataList[i].imageFile = FileUtils::getInstance()->getWritablePath() + temp;
		sPos = ePos + 1;
		/*读取存档时间*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//cocos2d::log(temp.c_str());
		_savedataList[i].date = temp;
		sPos = ePos + 1;
		/*读取存档文本*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//cocos2d::log(temp.c_str());
		_savedataList[i].text = temp;
		sPos = ePos + 1;
	}
}

bool GameSystem::loadGameSceneInfo(int i)
{
	char path[] = "savedata/savedata";
	char ch[4];
	sprintf(ch, "%d", i + 1);
	char file[100];
	sprintf(file, "%s%s%s%s", FileUtils::getInstance()->getWritablePath().c_str(), path, ch, ".sav");
	std::string data = FileUtils::getInstance()->getStringFromFile(file);
	if (_gameSceneInfo)	//删掉旧信息
	{
		//delete _gameSceneInfo;
		_gameSceneInfo = nullptr;
	}
	_gameSceneInfo = new GameData;
	if (data.compare("") != 0)
	{
		int sPos = 0;	//行头
		int ePos = 0;	//行尾
		std::string temp;	//临时储存一行信息
		/*丢弃读取存档截图路径*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//_savedataList[i].imageFile = temp;
		sPos = ePos + 1;
		/*丢弃读取存档时间*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//_savedataList[i].date = temp;
		sPos = ePos + 1;
		/*丢弃读取存档文本*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		_gameSceneInfo->currentText = temp;
		sPos = ePos + 1;
		/*读取当前名字*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentName = temp;
		/*读取当前背景key*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->backgroundKey = temp;
		/*读取当前立绘数量*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->charactorCount = atoi(temp.c_str());

		/*读取当前立绘信息*/
		for (int j = 0; j < _gameSceneInfo->charactorCount; j++)
		{
			/*读取角色key*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->fgCharactors[j].name = temp;
			/*读取角色表情*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->fgCharactors[j].face = temp;
			/*读取角色位置*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1; 
			_gameSceneInfo->fgCharactors[j].number = atoi(temp.c_str());
		}
		/*读取当前BGM信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->bgmKey = temp;
		/*读取当前sound信息*/

		/*读取当前选项信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->optionsNumber = atoi(temp.c_str());
		for (int j = 0; j < _gameSceneInfo->optionsNumber; j++)
		{
			std::string sign;
			std::string text;
			ePos = data.find('\n', sPos);
			sign = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			ePos = data.find('\n', sPos);
			text = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->options.insert(std::pair<std::string, std::string>(sign, text));
		}
		/*读取当前sign信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentSignName = temp;
		/*读取当前commandIndex信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentCommandIndex = atoi(temp.c_str());
        /*读取变量信息*/
        ePos = data.find('\n', sPos);
        temp = data.substr(sPos, ePos - sPos - 1);
        sPos = ePos + 1;
        stringToDataValue(temp);

		log("Load done.");
		return true;
	}
	else
	{
		log("%s not found", file);
		return false;
	}
}

void GameSystem::setGameScene(Scene* scene)
{
	_gameScene = scene;
}

Scene* GameSystem::getGameScene()
{
	return _gameScene;
}

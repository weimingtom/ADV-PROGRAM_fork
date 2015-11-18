#pragma once
#include "cocos2d.h"
#include "ScriptReader\CharactorManager.h"
#include <list>

#define SYSTEMVOLUME "SystemVolume"
#define MUSICVOLUME "MusicVolume"
#define SOUNDVOLUME "SoundVolume"
#define TEXTSPEED "TextSpeed"
#define AUTOSPEED "AutoSpeed"

struct fgCharactor
{
	std::string name;
	std::string face;
	int number;	//记录序号
	fgCharactor(std::string name, std::string face, int number)
		: name(name)
		, face(face)
		, number(number){};
};

/*用来储存当前游戏画面信息的数据结构*/
struct GameData	
{
	std::list<fgCharactor*> fgCharactors;	//储存角色，上限为三个
	std::string backgroundKey;
	std::string bgmKey;
	std::string soundKey;
	int charactorCount;	//立绘个数
};

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
	GameData* _gameSceneInfo;	//记录当前游戏画面信息


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

	void setSavedata(int i, bool value);
	bool getSavedata(int i);

	GameData* getGameSceneInfo();//获取游戏信息
	void setGameSceneInfo(GameData* gameData);//设置游戏信息，从GameScene中传入GameData*
	void saveGameSceneInfo(int i);//将GameData转成文档，储存在i位置
	void loadGameSceneInfo(int i);//将i位置的文件作为存档读取为GameData
};


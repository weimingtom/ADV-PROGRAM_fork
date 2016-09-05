#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "cocos2d.h"
#include "ScriptReader/CharactorManager.h"
#include <list>

#define SYSTEMVOLUME "SystemVolume"
#define MUSICVOLUME "MusicVolume"
#define SOUNDVOLUME "SoundVolume"
#define TEXTSPEED "TextSpeed"
#define AUTOSPEED "AutoSpeed"
#define ISSKIPREAD "IsSkipRead"

USING_NS_CC;

struct fgCharactor
{
	std::string name;
	std::string face;
	int number;	//记录序号
	fgCharactor(){};
	fgCharactor(std::string name, std::string face, int number)
		: name(name)
		, face(face)
		, number(number){};
};

/*用来储存当前游戏画面信息的数据结构*/
struct GameData
{
	fgCharactor fgCharactors[3];	//储存角色，上限为三个
	std::string backgroundKey;	//背景key
	std::string bgmKey;	//背景音乐key
	std::string soundKey;	//音效key
	int charactorCount;	//立绘个数
	std::string currentSignName;	//脚本标签
	int currentCommandIndex;	//脚本位置
	std::string currentName;	//当前名字
	std::string currentText;	//当前文本
	int optionsNumber;
	std::map<std::string, std::string> options;
};

struct GameSaveData
{
	std::string imageFile;
	std::string date;
	std::string text;
	GameSaveData()
	{
		imageFile = "";
		date = "";
		text = "";
	}
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
	GameSaveData* _savedataList; //记录当前游戏的存档信息
	bool _isLoadSuccess;	//是够载入成功
	RenderTexture* _screenShoot;	//储存屏幕截图
    
	//界面管理
	Scene* _gameScene;	//游戏主画面

public:
	GameSystem();
	~GameSystem();
	static GameSystem* getInstance();
	static void destoryInstance();
	void setDefault();

	void setSystemVolume(float value);
	void setMusicVolume(float value);
	void setSoundVolume(float value);
	void setTextSpeed(float value);
	void setAutoSpeed(float value);
    void setHaveRead(const std::string &key, int value);
    void setIsSkipRead(bool value); //设置是否跳过已阅

	float getSystemVolume();
	float getMusicVolume();
	float getSoundVolume();
	float getTextSpeed();
	float getAutoSpeed();
    int getHaveRead(const std::string &key);
    bool getIsSkipRead();

    /*--处理变量存取部分--*/
    //将key设为value值
	void setDataValue(std::string &key, int value);
    //获得key的value值，如果key不存在会返回0。使用前先用isDataValueExists(const std::string &key)判断一下变量是否存在。
	int getDataValue(std::string &key);
    //判断key变量是否存在于变量池中，返回布尔值。
    bool isDataValueExists(const std::string &key);
    //我忘了这是啥
	void setData(std::map<std::string, int> *map = nullptr);
    //将变量池转为string，用于变量池储存为存档数据。
    std::string dataValueToString();
    //将string转为变量池，用于读取存档数据为变量池。
    void stringToDataValue(const std::string &dataValueStr);
    
    //存档管理
	void setSavedata(int i, bool value);	//设置存档是否存在，value为true时则有存档
	bool getSavedata(int i);

	GameData* getGameSceneInfo();//获取游戏信息
	void setGameSceneInfo(GameData* gameData);//设置游戏信息，从GameScene中传入GameData*
	void saveGameSceneInfo(int i);//将GameData转成文档，储存在i位置
	bool loadGameSceneInfo(int i);//将i位置的文件作为存档读取为GameData

	void setIsLoadSuccess(bool value);
	bool getIsLoadSuccess();

	void initGameSavedataList();	//初始化存档列表
	GameSaveData* getGameSavedata(int i);	//获取单个存档信息
	void updateGameSavedata(int i);	//重新加载单个存档信息
	void deleteGameSavedata(int i);	//删除某个存档信息
	bool loadGameSavedata(int i);	//读取某个存档信息

	void createSavedata();

	void setScreenShoot(RenderTexture* render);	
	RenderTexture* getScreenShoot();

	void setGameScene(Scene* scene);	//设置游戏场景
	Scene* getGameScene();	//获取游戏场景
	
    float getPosition(CMPositionType pt);
};

#endif


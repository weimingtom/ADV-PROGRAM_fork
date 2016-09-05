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
	int number;	//��¼���
	fgCharactor(){};
	fgCharactor(std::string name, std::string face, int number)
		: name(name)
		, face(face)
		, number(number){};
};

/*�������浱ǰ��Ϸ������Ϣ�����ݽṹ*/
struct GameData
{
	fgCharactor fgCharactors[3];	//�����ɫ������Ϊ����
	std::string backgroundKey;	//����key
	std::string bgmKey;	//��������key
	std::string soundKey;	//��Чkey
	int charactorCount;	//�������
	std::string currentSignName;	//�ű���ǩ
	int currentCommandIndex;	//�ű�λ��
	std::string currentName;	//��ǰ����
	std::string currentText;	//��ǰ�ı�
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
	static GameSystem* _instance;	//ʵ��
	
	//����
	float _systemVolume;	//������
	float _musicVolume;	//��������
	float _soundVolume;	//��Ч����

	//�ݳ����
	float _textSpeed;		//�����ٶ�
	float _autoSpeed;		//�Զ��ٶ�

	//ϵͳ����
	
	std::map<std::string, int>* _savedata;		//��Ϸ����
	GameData* _gameSceneInfo;	//��¼��ǰ��Ϸ������Ϣ
	GameSaveData* _savedataList; //��¼��ǰ��Ϸ�Ĵ浵��Ϣ
	bool _isLoadSuccess;	//�ǹ�����ɹ�
	RenderTexture* _screenShoot;	//������Ļ��ͼ
    
	//�������
	Scene* _gameScene;	//��Ϸ������

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
    void setIsSkipRead(bool value); //�����Ƿ���������

	float getSystemVolume();
	float getMusicVolume();
	float getSoundVolume();
	float getTextSpeed();
	float getAutoSpeed();
    int getHaveRead(const std::string &key);
    bool getIsSkipRead();

    /*--���������ȡ����--*/
    //��key��Ϊvalueֵ
	void setDataValue(std::string &key, int value);
    //���key��valueֵ�����key�����ڻ᷵��0��ʹ��ǰ����isDataValueExists(const std::string &key)�ж�һ�±����Ƿ���ڡ�
	int getDataValue(std::string &key);
    //�ж�key�����Ƿ�����ڱ������У����ز���ֵ��
    bool isDataValueExists(const std::string &key);
    //����������ɶ
	void setData(std::map<std::string, int> *map = nullptr);
    //��������תΪstring�����ڱ����ش���Ϊ�浵���ݡ�
    std::string dataValueToString();
    //��stringתΪ�����أ����ڶ�ȡ�浵����Ϊ�����ء�
    void stringToDataValue(const std::string &dataValueStr);
    
    //�浵����
	void setSavedata(int i, bool value);	//���ô浵�Ƿ���ڣ�valueΪtrueʱ���д浵
	bool getSavedata(int i);

	GameData* getGameSceneInfo();//��ȡ��Ϸ��Ϣ
	void setGameSceneInfo(GameData* gameData);//������Ϸ��Ϣ����GameScene�д���GameData*
	void saveGameSceneInfo(int i);//��GameDataת���ĵ���������iλ��
	bool loadGameSceneInfo(int i);//��iλ�õ��ļ���Ϊ�浵��ȡΪGameData

	void setIsLoadSuccess(bool value);
	bool getIsLoadSuccess();

	void initGameSavedataList();	//��ʼ���浵�б�
	GameSaveData* getGameSavedata(int i);	//��ȡ�����浵��Ϣ
	void updateGameSavedata(int i);	//���¼��ص����浵��Ϣ
	void deleteGameSavedata(int i);	//ɾ��ĳ���浵��Ϣ
	bool loadGameSavedata(int i);	//��ȡĳ���浵��Ϣ

	void createSavedata();

	void setScreenShoot(RenderTexture* render);	
	RenderTexture* getScreenShoot();

	void setGameScene(Scene* scene);	//������Ϸ����
	Scene* getGameScene();	//��ȡ��Ϸ����
	
    float getPosition(CMPositionType pt);
};

#endif


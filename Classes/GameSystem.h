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
	bool _isNewGame;	//��GameScene�ж��Ƿ�ʼ����Ϸ��falseΪ����

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

	void setSavedata(int i, bool value);	//���ô浵�Ƿ���ڣ�valueΪtrueʱ���д浵
	bool getSavedata(int i);

	GameData* getGameSceneInfo();//��ȡ��Ϸ��Ϣ
	void setGameSceneInfo(GameData* gameData);//������Ϸ��Ϣ����GameScene�д���GameData*
	void saveGameSceneInfo(int i);//��GameDataת���ĵ���������iλ��
	void loadGameSceneInfo(int i);//��iλ�õ��ļ���Ϊ�浵��ȡΪGameData

	void setIsNewGame(bool value);
	bool getIsNewGame();
};


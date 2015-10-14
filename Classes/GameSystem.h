#pragma once
#include "cocos2d.h"

#define SYSTEMVOLUME "SystemVolume"
#define MUSICVOLUME "MusicVolume"
#define SOUNDVOLUME "SoundVolume"
#define TEXTSPEED "TextSpeed"
#define AUTOSPEED "AutoSpeed"

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

};


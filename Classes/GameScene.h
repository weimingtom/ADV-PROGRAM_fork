#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"

#define MAX_CHARACTOR_NUMBER 5

class GameScene : public cocos2d::Layer
{
	cocos2d::Label* _label;//�ı�����ı���
	//ScriptReader* _reader;	//�ű�������

	Label* _nameLabel;	//������
	CharLabel* _textLabel;	//�԰׿�
	Sprite* _dialogWindow;	//�ı��򱳾�
	Layer* _backgroundLayer;	//������
	Sprite* _backgroundSprite;	//����ͼƬ
	Layer* _charactorsLayer;	//�����
	Layer* _selectLayer;	//ѡ���

	Charactor* _chars[MAX_CHARACTOR_NUMBER];	//���浱ǰ��������
	Charactor* _emptyChar;	//�ս�ɫ
	int _charNumber;	//������������

	bool _isPlayingMusic;	//���ֲ���״̬

	std::string _backgroundKey;	//��ǰ����
	std::string _backgroundMusicKey;	//��ǰ��������
	std::string _soundKey;	//��ǰ��Ч
	std::string _currentText;	//��ǰ�ı�
	std::string _currentName;	//��ǰ����
	std::map<std::string, std::string> _currentOptions;	//��ǰѡ��
	int _optionsNumber;	//��ǰѡ������

public:
	GameScene();
	~GameScene();
	
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float dt);

	void updateLabel(std::string text);

	void showName(std::string &name);	//������

	void showText(std::string &text);	//��ʾ�ı�

	void showClickSign();	//�������ͼ��

	void screenClicked();	//��Ļ����¼������˰�ť���Ի���

	void dialogClicked();	//��ʾ��һ��Ի�

	void changeBackground(std::string &key);	//�л�����

	void playBackgroundMusic(std::string &key);	//��������
	void stopBackgroundMusic();						//ֹͣ����
	void scheduleVolumeFadeIn();	//���ֵ���
	void scheduleVolumeFadeOut();	//���ֵ���

	void playSound(std::string &file);	//������Ч
	void stopSound();					//ֹͣ��Ч

	void startAutoPlay();	//��ʼ�Զ�ǰ��
	void stopAutoPlay();	//ֹͣ�Զ�ǰ��
	void autoPlay(float dt);	//�Զ�ǰ��

	void displayCharator(std::string cName,std::string face);
	void unDisplayCharator(std::string cName);

	void createGameDate();

	void showSaveScene();	//����浵����
	void showLoadScene();	//�����������

	void ScreenShoot();	//����

	void clear();	//�����Ļ�����ж���
	void reloadScene();	//���س�����ͨ��������

	void showSelect(std::map<std::string, std::string> &options);	//��ʾѡ��
};


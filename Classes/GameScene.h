#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"


class GameScene : public cocos2d::Layer
{
	cocos2d::Label* _label;//�ı�����ı���
	ScriptReader* _reader;	//�ű�������

	Label* _nameLabel;	//������
	CharLabel* _textLabel;	//�԰׿�
	Sprite* _dialogWindow;	//�ı��򱳾�
	Layer* _backgroundLayer;	//������
	Sprite* _backgroundSprite;	//����ͼƬ
	Layer* _charactorsLayer;	//�����

	Charactor* _chars[5];	//���浱ǰ��������
	int _charNumber;	//������������

	bool _isPlayingMusic;	//���ֲ���״̬

	std::string _backgroundKey;	//��ǰ����
	std::string _backgroundMusicKey;	//��ǰ��������
	std::string _soundKey;	//��ǰ��Ч

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
};


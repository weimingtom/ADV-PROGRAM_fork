#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"


class GameScene : public cocos2d::Layer
{
	cocos2d::Label* _label;//�ı�����ı���
	ScriptReader* _reader;	//�ű�������

	Label* _nameLabel;	//������
	CharLabel* _textLabel;	//�԰׿�
	Sprite* _dialogWindow;	//�ı��򱳾�
	Layer* _backgroundLayer;	//������
	Sprite* _backgroundSprite;	//����ͼƬ

	bool _isPlayingMusic;	//���ֲ���״̬
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

	void changeBackground(Sprite &background);	//�л�����

	void playBackgroundMusic(std::string &file);	//��������
	void stopBackgroundMusic();						//ֹͣ����
	void scheduleVolumeFadeIn();	//���ֵ���
	void scheduleVolumeFadeOut();	//���ֵ���

	void playSound(std::string &file);	//������Ч
	void stopSound();					//ֹͣ��Ч
};


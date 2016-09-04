
#ifndef GAMESCENE_H

#define GAMESCENE_H

#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"
#include "ui/CocosGUI.h"

#define MAX_CHARACTOR_NUMBER 5

#define TEXTLABEL_SIZE_WIDTH 800
#define TEXTLABEL_SIZE_HEIGHT 100

#define SCREEN_SHOOT_WIDTH 100
#define SCREEN_SHOOT_HEIGHT 80

USING_NS_CC;
using namespace ui;

class GameScene : public cocos2d::Layer
{
	cocos2d::Label* _label;//�ı�����ı���
	//ScriptReader* _reader;	//�ű�������

	Label* _nameLabel;	//������
    Sprite* _nameWindow;
	CharLabel* _textLabel;	//�԰׿�
	Sprite* _dialogWindow;	//�ı��򱳾�
	Layer* _backgroundLayer;	//������
	Sprite* _backgroundSprite;	//����ͼƬ
	Layer* _charactorsLayer;	//�����
	Layer* _selectLayer;	//ѡ���
    Sprite* _wtIcon;
    
    //���ڰ�ť
    CheckBox* CBskip;   //���
    CheckBox* CBauto;   //�Զ�
    
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

    void showMenuSceneYes();    
    void showMenuSceneNo();
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
    void startSkipPlay();
    void stopSkipPlay();
	void autoPlay(float dt);	//�Զ�ǰ��
    void skipPlay(float dt);    //���
    
    void selectEventOfSkip(Ref* pSender,CheckBox::EventType type);
    void selectEventOfAuto(Ref* pSender,CheckBox::EventType type);
    
	void displayCharator(std::string cName,std::string face);
	void unDisplayCharator(std::string cName);

	void createGameDate();

	void showSaveScene();	//����浵����
	void showLoadScene();	//�����������
	void showHistoryScene();	//������ʷ��¼����
    void showMenuScene();       //�������˵�

	void ScreenShoot();	//����

	void clear();	//�����Ļ�����ж���
	void reloadScene();	//���س�����ͨ��������

	void showSelect(std::map<std::string, std::string> &options);	//��ʾѡ��
    
    void skipAction();
    void showWaittingAnime();
    void hideWaittingAnime();
    
};

#endif

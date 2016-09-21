#ifndef SETTING_SCENE_H
#define SETTING_SCENE_H

#include "cocos2d.h"
//#include "Control/RadioButton.h"
//#include "Control/Slidebar.h"

USING_NS_CC;

class RadioButton;

class Slidebar;

class SettingScene : public Layer
{
	//��ѡ��ť��
	RadioButton* _isWindow;	//����orȫ��
    RadioButton* _isSkipAll;	//�Ƿ���������
	//������
	Slidebar* _musicVolumeSlidebar;	//�����������ڻ�����
	Slidebar* _soundVolumeSlidebar;	//��Ч�������ڻ�����
	Slidebar* _autoSpeedSlidebar;	//�Զ�ǰ���ٶȻ�����
	Slidebar* _skipSpeedSlidebar;	//����ǰ���ٶȻ�����
    Slidebar* _textSpeedSlb;        //�ı���ʾ�ٶ�
public:
	SettingScene();
	~SettingScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);

	void back();	//����
	void test();	//���Է���
	void changeMusicVolume();   //�ı���������
    void changeSoundVolume();   //�ı���Ч����
    void changeTextSpeed();     //�ı��ı���ʾ�ٶ�
    void changeAutoSpeed();     //�ı��Զ������ٶ�
    void changeIsSkipAll();     //�ı��Ƿ�����ȫ��
};

#endif

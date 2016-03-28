#ifndef EASYBUTTON_H
#define EASYBUTTON_H

#include "cocos2d.h"

USING_NS_CC;
/*
���Ǽ򻯰��Button��Ϊ����ϵ�ѡ��ť�����Ƶİ�ť��
*/
class EasyButton : public Node
{
	Sprite* _normal;	//��ͨ״̬��ͼƬ
	Sprite* _touch;		//����״̬��ͼƬ
	Sprite* _selected;	//ѡ��״̬��ͼƬ
	EventListenerTouchOneByOne* _eventTouch;	//�����¼�
public:
	EasyButton(Sprite* _normalSprite, Sprite* _touchSprite, Sprite* _selectedSprite);
	~EasyButton();
	static EasyButton* createEasyButton(const std::string &_normalFile);
	static EasyButton* createEasyButton(const std::string &_normalFile, const std::string &_touchFile);
	static EasyButton* createEasyButton(const std::string &_normalFile, const std::string &_touchFile, const std::string &_selectedFile);

	void onTouchBegan(Touch *t, Event *e);
	void onTouchMoved(Touch *t, Event *e);
	void onTouchEnded(Touch *t, Event *e, bool flag);

	void setEventTouchEnabled(bool flag);	//���ü���������
	Sprite* getNormal();	//������ͨ״̬�ľ���

	std::function<void()> touchEvent;	//�����¼�����ָ��
	//std::function<void(int i)> touchEventWithInt;	//��int�����Ĵ����¼�����ָ��
};

#endif
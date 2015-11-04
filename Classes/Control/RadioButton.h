#pragma once
#include "cocos2d.h"
#include "EasyButton.h"

USING_NS_CC;

class RadioButton : public Node
{
	std::vector<EasyButton*>* _radios;	//��ѡ��ť��
	int _selected;	//��ǰѡ�еİ�ť�±�
public:
	RadioButton();
	~RadioButton();
	static RadioButton* createRadioButton(EasyButton* i, ...);
	void touchEvent(int i);
	//void touchEvent();	//����
};


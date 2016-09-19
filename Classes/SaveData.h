#ifndef SAVEDATA_H
#define SAVEDATA_H
#include "cocos2d.h"
#include "GameSystem.h"

#define TEXT_MAX_LENGTH 500

USING_NS_CC;

class SaveData : public Node
{
	/*������Ϣ*/
	std::string _imageFile;	//�浵��ͼ·��
	int _number;	//�浵���
	std::string _text;	//�浵��Ϣ
	std::string _other;	//��ע��Ϣ
	std::string _date;	//�浵ʱ��

	Sprite* _dataImage;	//��ͼ
	Label* _dataText;	//�ı���
	Label* _dataDate;	//ʱ��

	Sprite* _stageLayer;	//����ײ�
    //Layer* _stageLayer;
    
public:
	SaveData(int number, std::string imageFile, std::string text, std::string date);
	SaveData(int number);
	~SaveData();
	void setOther();	//���ñ�ע��Ϣ
	static SaveData* create(int i);	//����һ��SaveData��ť
	std::function <void(int)> onTouchEnded;
	void updataData();	//ˢ�°�ť����
	Sprite* getStageLayer();
};

#endif

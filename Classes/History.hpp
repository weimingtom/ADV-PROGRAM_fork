#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
#define MAXIMUM 80 //����¼��
/*��¼����*/
enum recordType
{
    null,   //�԰ף�Ĭ�ϣ�
    talk,   //�԰�
    selecte  //ѡ��
};

/*��¼*/
struct record
{
    recordType type;    //��¼����
    std::string text;   //��¼�ı�
    std::string name;   //��¼��ɫ��
    Color4B color;      //��¼��ɫ
    record(recordType type, std::string text, std::string name = "", Color4B color = Color4B::WHITE)
        : type(type)
        , text(text)
        , name(name)
        , color(color)
    {
        
    };
};

class HistoryLogger
{
    int _maximum;   //����¼��
    int _currentLog;    //��ǰ��¼
    record* _records[MAXIMUM];
    static HistoryLogger* _instance;    //ʵ��
public:
    HistoryLogger();
    ~HistoryLogger();
    static HistoryLogger* getInstance(); //��ȡʵ��
	void destoryInstance(); //����ʵ��
	record* createRecord(const std::string type, std::string text, std::string name, Color4B color = Color4B::WHITE);    //���ɼ�¼
	void addRecord(const std::string type, std::string text, std::string name, Color4B color = Color4B::WHITE);
    void pushRecord(record record);
	void addRecord(record* record);	//��Ӽ�¼
	int getLength();	//��ȡ��ǰ��ʷ��¼����
	record* getRecord(int i);
};

#endif
#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
#define MAXIMUM 80 //最大记录数
/*记录类型*/
enum recordType
{
    null,   //旁白（默认）
    talk,   //对白
    selecte  //选项
};

/*记录*/
struct record
{
    recordType type;    //记录类型
    std::string text;   //记录文本
    std::string name;   //记录角色名
    Color4B color;      //记录颜色
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
    int _maximum;   //最大记录数
    int _currentLog;    //当前记录
    record* _records[MAXIMUM];
    static HistoryLogger* _instance;    //实例
public:
    HistoryLogger();
    ~HistoryLogger();
    static HistoryLogger* getInstance(); //获取实例
	void destoryInstance(); //销毁实例
	record* createRecord(const std::string type, std::string text, std::string name, Color4B color = Color4B::WHITE);    //生成记录
	void addRecord(const std::string type, std::string text, std::string name, Color4B color = Color4B::WHITE);
    void pushRecord(record record);
	void addRecord(record* record);	//添加记录
	int getLength();	//获取当前历史记录条数
	record* getRecord(int i);
};

#endif
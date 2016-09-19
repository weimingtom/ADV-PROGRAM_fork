#ifndef SAVEDATA_H
#define SAVEDATA_H
#include "cocos2d.h"
#include "GameSystem.h"

#define TEXT_MAX_LENGTH 500

USING_NS_CC;

class SaveData : public Node
{
	/*基本信息*/
	std::string _imageFile;	//存档截图路径
	int _number;	//存档序号
	std::string _text;	//存档信息
	std::string _other;	//备注信息
	std::string _date;	//存档时间

	Sprite* _dataImage;	//截图
	Label* _dataText;	//文本层
	Label* _dataDate;	//时间

	Sprite* _stageLayer;	//储存底层
    //Layer* _stageLayer;
    
public:
	SaveData(int number, std::string imageFile, std::string text, std::string date);
	SaveData(int number);
	~SaveData();
	void setOther();	//设置备注信息
	static SaveData* create(int i);	//创建一个SaveData按钮
	std::function <void(int)> onTouchEnded;
	void updataData();	//刷新按钮数据
	Sprite* getStageLayer();
};

#endif

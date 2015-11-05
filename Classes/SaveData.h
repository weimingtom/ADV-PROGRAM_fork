#pragma once
#include "cocos2d.h"
#include "GameSystem.h"

USING_NS_CC;

class SaveData : public Node
{
	/*基本信息*/
	std::string _imageFile;	//存档截图路径
	int _number;	//存档序号
	std::string _text;	//存档信息
	std::string _other;	//备注信息
	std::string _date;	//存档时间
public:
	SaveData(int number, std::string imageFile, std::string text, std::string date);
	~SaveData();
	void setOther();	//设置备注信息
};


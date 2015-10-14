#pragma once
#include "ScriptCommand.h"
#include "ScriptReader.h"

class ScriptReader::SCSet : public ScriptCommand
{
	char _mark;	//����������ţ�Ŀǰ����'+','-','='��������
	std::string _key;	//Ŀ�����
	int _value;		//ֵ
public:
	SCSet(ScriptReader *reader, std::string &key, char mark, int value);
	~SCSet();
	void execute(cocos2d::Node* stage);

	std::function<void(std::string &key, int value)> setDataValue;
	std::function<int(std::string &key)> getDataValue;
	std::function<void(std::string &key, int value)> setDataValue;

}; 

 
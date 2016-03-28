#ifndef __SC_SET_H__
#define __SC_SET_H__
#include "ScriptCommand.h"
#include "ScriptReader.h"

class ScriptReader::SCSet : public ScriptCommand
{
	char _mark;	//储存操作符号，目前仅有'+','-','='三个符号
	std::string _key;	//目标变量
	int _value;		//值
public:
	SCSet(ScriptReader *reader, std::string &key, char mark, int value);
	~SCSet();
	void execute(cocos2d::Node* stage);

	void setDataValue(std::string key,int value);
	int getDataValue(std::string key);

}; 

#endif
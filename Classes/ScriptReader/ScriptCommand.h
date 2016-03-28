#ifndef __SCRIPT_COMMAND_H__
#define __SCRIPT_COMMAND_H__
#include "ScriptReader.h"
class ScriptReader::ScriptCommand{
public:
	ScriptCommandType type;	//命令类型
	ScriptReader *reader;	//脚本解析器
	void execute(cocos2d::Node* stage);	//执行方法
};

#endif
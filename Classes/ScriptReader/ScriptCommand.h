#ifndef __SCRIPT_COMMAND_H__
#define __SCRIPT_COMMAND_H__
#include "ScriptReader.h"
class ScriptReader::ScriptCommand{
public:
	ScriptCommandType type;	//��������
	ScriptReader *reader;	//�ű�������
	void execute(cocos2d::Node* stage);	//ִ�з���
};

#endif
#ifndef __SC_JUMP_H__
#define __SC_JUMP_H__
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCJump :public ScriptCommand
{
public:
	std::string sign;	//Ìø×ªµÄ±êÇ©
	SCJump(ScriptReader* reader, std::string &sign);
	~SCJump();
	void execute(cocos2d::Node* stage);
};

#endif
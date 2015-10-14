#pragma once
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCLeave:public ScriptCommand
{
public:
	std::string cName;
	SCLeave(ScriptReader *reader, std::string &name);
	~SCLeave();
	void execute(cocos2d::Node* stage);
};


#pragma once
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCStopBGM : public ScriptCommand
{
public:
	SCStopBGM(ScriptReader *reader);
	~SCStopBGM();

	void execute(cocos2d::Node* stage);
};


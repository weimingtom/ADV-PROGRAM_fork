#pragma once
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCStopSound : public ScriptCommand
{
public:
	SCStopSound(ScriptReader *reader);
	~SCStopSound();

	void execute(cocos2d::Node* stage);
};


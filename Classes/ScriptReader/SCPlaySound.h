#pragma once
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCPlaySound : public ScriptCommand
{
public:
	SCPlaySound(ScriptReader *reader, std::string key);
	~SCPlaySound();

	std::string key;

	void execute(cocos2d::Node* stage);
};


#ifndef __SC_BACKGROUND_H__
#define __SC_BACKGROUND_H__

#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCBackground : public ScriptCommand
{
public:
	SCBackground(ScriptReader *reader, std::string key);
	~SCBackground();

	std::string key;

	void execute(cocos2d::Node* stage);
};

#endif
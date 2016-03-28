#ifndef __SC_PLAY_BGM_H__
#define __SC_PLAY_BGM_H__
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCPlayBGM : public ScriptCommand
{
public:
	SCPlayBGM(ScriptReader *reader, std::string key);
	~SCPlayBGM();

	std::string key;

	void execute(cocos2d::Node* stage);
};

#endif
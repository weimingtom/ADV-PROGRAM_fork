#ifndef __SC_PLAY_SOUND_H__
#define __SC_PLAY_SOUND_H__
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

#endif
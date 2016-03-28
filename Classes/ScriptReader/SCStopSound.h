#ifndef __SC_STOP_SOUND_H__
#define __SC_STOP_SOUND_H__
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCStopSound : public ScriptCommand
{
public:
	SCStopSound(ScriptReader *reader);
	~SCStopSound();

	void execute(cocos2d::Node* stage);
};

#endif
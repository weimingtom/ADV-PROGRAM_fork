#include "SCStopSound.h"


ScriptReader::SCStopSound::SCStopSound(ScriptReader *reader)
{
	this->reader = reader;
	this->type = ScriptCommandType::StopSd;
}


ScriptReader::SCStopSound::~SCStopSound()
{
}

void ScriptReader::SCStopSound::execute(cocos2d::Node* stage)
{
	reader->stopSound();

	reader->nextScript();
}

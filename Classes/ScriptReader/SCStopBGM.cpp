#include "SCStopBGM.h"


ScriptReader::SCStopBGM::SCStopBGM(ScriptReader *reader)
{
	this->reader = reader;
	this->type = ScriptCommandType::StopBGM;
}


ScriptReader::SCStopBGM::~SCStopBGM()
{
}

void ScriptReader::SCStopBGM::execute(cocos2d::Node* stage)
{
	reader->stopBackgroundMusic();

	reader->nextScript();
}

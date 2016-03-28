#include "SCBackground.h"
#include "BackgroundManager.h"


ScriptReader::SCBackground::SCBackground(ScriptReader *reader, std::string key)
	:key(key)
{
	this->reader = reader;
	this->type = ScriptCommandType::Background;
}


ScriptReader::SCBackground::~SCBackground()
{
}


void ScriptReader::SCBackground::execute(cocos2d::Node* stage)
{
	reader->changeBackground(key);
	reader->nextScript();
}
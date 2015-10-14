#include "SCJump.h"


ScriptReader::SCJump::SCJump(ScriptReader* reader, std::string &sign)
	:sign(sign)
{
	this->reader = reader;
	this->type = ScriptCommandType::Jump;
}


ScriptReader::SCJump::~SCJump()
{
}

void ScriptReader::SCJump::execute(cocos2d::Node* stage)
{
	reader->jumpToSign(sign);
}

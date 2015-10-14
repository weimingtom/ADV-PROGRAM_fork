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
	auto background = BM->getBackground(key);
	auto backgroundSprite = Sprite::create(background);
	backgroundSprite->setAnchorPoint(Vec2(0, 0));
	reader->changeBackground(*backgroundSprite);
}
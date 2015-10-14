#include "SCSet.h"
#include "GameSystem.h"


ScriptReader::SCSet::SCSet(ScriptReader* reader, std::string &key, char mark, int value)
	: _key(key)
	, _mark(mark)
	, _value(value)
{
	this->reader = reader;
	this->type = ScriptCommandType::Set;
	this->setDataValue = CC_CALLBACK_2(GameSystem::setDataValue, GameSystem::getInstance());
	this->getDataValue = CC_CALLBACK_1(GameSystem::getDataValue, GameSystem::getInstance());
}


ScriptReader::SCSet::~SCSet()
{
}

void ScriptReader::SCSet::execute(cocos2d::Node* stage)
{
	switch (_mark)
	{
	case '=':
		setDataValue(_key, _value);
		break;
	case '-':
		setDataValue(_key, getDataValue(_key) - _value);
		break;
	case '+':
		setDataValue(_key, getDataValue(_key) + _value);
		break;
	default:

	}
}
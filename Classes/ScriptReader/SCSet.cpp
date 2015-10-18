#include "SCSet.h"
#include "GameSystem.h"


ScriptReader::SCSet::SCSet(ScriptReader* reader, std::string &key, char mark, int value)
	: _key(key)
	, _mark(mark)
	, _value(value)
{
	this->reader = reader;
	this->type = ScriptCommandType::Set;
}


ScriptReader::SCSet::~SCSet()
{
}

void ScriptReader::SCSet::execute(cocos2d::Node* stage)
{
	switch (_mark)
	{
	case '=':
		break;
	case '-':
		_value = getDataValue(_key) - _value;
		break;
	case '+':
		_value = getDataValue(_key) + _value;
		break;
	default:
		log("SC>Set:Unknow Symbol.");
		break;
	}
	setDataValue(_key, _value);
	log("SC>Set:%s=%d",_key.c_str(),_value);

	reader->nextScript();
}

void ScriptReader::SCSet::setDataValue(std::string key, int value)
{
	GameSystem::getInstance()->setDataValue(key, value);
}

int ScriptReader::SCSet::getDataValue(std::string key)
{
	return GameSystem::getInstance()->getDataValue(key);
}
#include "SCPlaySound.h"
#include "SoundManager.h"

ScriptReader::SCPlaySound::SCPlaySound(ScriptReader *reader, std::string key)
	:key(key)
{
	this->reader = reader;
	this->type = ScriptCommandType::PlaySd;
}


ScriptReader::SCPlaySound::~SCPlaySound()
{
}

void ScriptReader::SCPlaySound::execute(cocos2d::Node* stage)
{
	auto sound = SM->getSound(key);
	if (sound.compare("") == 0)
	{
		log("SC> unfine bgm %s", key.c_str());
	}
	else
	{
		reader->playSound(sound);
	}

	reader->nextScript();
}

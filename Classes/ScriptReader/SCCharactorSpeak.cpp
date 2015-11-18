#include "SCCharactorSpeak.h"
#include "CharactorManager.h"
#include "GameSystem.h"

ScriptReader::SCCharactorSpeak::SCCharactorSpeak(ScriptReader *reader, std::string &name, std::string &text, std::string &face)
	:cName(name)
	, face(face)
	, text(text)
{
	this->reader = reader;
	this->type = ScriptCommandType::CharactorSpeak;
}

ScriptReader::SCCharactorSpeak::~SCCharactorSpeak()
{

}

void ScriptReader::SCCharactorSpeak::execute(cocos2d::Node* stage)
{
    auto cha = CM->getCharactor(cName);
	reader->showCharator(cName, face);
	reader->showName(cha->name);
	reader->showText(text);
	cocos2d::log("%s",text.c_str());
}
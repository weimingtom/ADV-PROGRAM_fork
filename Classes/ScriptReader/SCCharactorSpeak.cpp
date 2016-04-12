#include "SCCharactorSpeak.h"
#include "CharactorManager.h"
#include "GameSystem.h"
#include "History.hpp"

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
	bool isName = true;
    Charactor* cha;
    if (cName.compare("") != 0)
    {
        cha = CM->getCharactor(cName);
        if (face.compare("") != 0)
            reader->showCharator(cName, face);
        reader->showName(cha->name);
    }
    else
    {
        isName = false;
        std::string nullstring = "";
        //reader->showName(&nullstring);
        reader->showName(nullstring);
    }
    if (text.compare("") == 0)
    {
        reader->nextScript();
    }
    else
    {
        reader->showText(text);
    }
        if (isName && text.compare(""))
        {
            HistoryLogger::getInstance()->addRecord("talk", text, cha->name);
        }
        else
        {
            HistoryLogger::getInstance()->addRecord("null", text, "");
        }
}
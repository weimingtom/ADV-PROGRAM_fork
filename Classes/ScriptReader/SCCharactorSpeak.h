#ifndef __SC_CHARACTOR_SPEAK_H__
#define __SC_CHARACTOR_SPEAK_H__
#include "ScriptReader.h"
#include "ScriptCommand.h"

//enum CharactorFaceType;

class ScriptReader::SCCharactorSpeak :public ScriptCommand
{
public:
	std::string cName;
	std::string face;
	std::string text;
	
	SCCharactorSpeak(ScriptReader *reader, std::string &name, std::string &text, std::string &face);

	~SCCharactorSpeak();

	void execute(cocos2d::Node* stage);


};

#endif
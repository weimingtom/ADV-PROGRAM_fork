#ifndef __SC_SELECT_H__
#define __SC_SELECT_H__
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCSelect:public ScriptCommand
{
public:
	SCSelect(ScriptReader *reader);
	~SCSelect();

	std::map<std::string, std::string> options;

	void addOption(std::string &sign, std::string &text);

	void execute(Node* stage);

};

#endif
//
//  History.cpp
//  
//
//  Created by Sunny on 15/10/23.
//
//

#include "History.hpp"

HistoryLogger::HistoryLogger()
    : _maximum(MAXIMUM)
{
    //_records = new record[MAXIMUM];
}

HistoryLogger::~HistoryLogger()
{
    
}

HistoryLogger* HistoryLogger::getInstance()
{
    if (!_instance)
    {
        _instance = new HistoryLogger;
    }
	return _instance;
}

void HistoryLogger::destoryInstance()
{
    if (_instance)
    {
        delete _instance;
        _instance = nullptr;
    }
}

record* HistoryLogger::createRecord(std::string type, std::string text, std::string name, Color4B color)
{
	/*将type从string转成recordType*/
    recordType tmpType;
	if (type.compare("null") == 0)
	{
		tmpType = recordType::null;
	}
	else if (type.compare("talk") == 0)
	{
		tmpType = recordType::talk;
	}
	else if (type.compare("select") == 0)
	{
		tmpType = recordType::selecte;
	}

    record* tmpRecord = new record(tmpType, text, name, color);
	return tmpRecord;
}

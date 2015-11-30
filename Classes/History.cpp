//
//  History.cpp
//  
//
//  Created by Sunny on 15/10/23.
//
//

#include "History.hpp"

HistoryLogger* HistoryLogger::_instance = nullptr;

HistoryLogger::HistoryLogger()
    : _maximum(MAXIMUM)
{
    //_records = new record[MAXIMUM];
	for (int i = 0; i < MAXIMUM; i++)
	{
		_records[i] = nullptr;
	}
	_currentLog = 0;
}

HistoryLogger::~HistoryLogger()
{
	for (int i = 0; i < MAXIMUM; i++)
	{
		CC_SAFE_DELETE(_records[i]);
	}
}

HistoryLogger* HistoryLogger::getInstance()
{
    if (!_instance)
    {
        _instance = new HistoryLogger();
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

void HistoryLogger::addRecord(std::string type, std::string text, std::string name, Color4B color)
{
	auto record = createRecord(type, text, name, color);
	addRecord(record);
}

void HistoryLogger::addRecord(record* record)
{
	if (_records[_currentLog] == nullptr)
	{
		_records[_currentLog] = record;
		_currentLog++;
	}
}
int HistoryLogger::getLength()
{
	return _currentLog;
}

record* HistoryLogger::getRecord(int i)
{
	return _records[i];
}
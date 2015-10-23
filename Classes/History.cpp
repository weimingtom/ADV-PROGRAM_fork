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
    _records = new record(MAXIMUM);
}

HistoryLogger::~HistoryLogger()
{
    
}

HistoryLogger HistoryLogger::getInstance()
{
    if (_instance)
    {
        return _instance;
    }
    else
    {
        _instance = new HistoryLogger;
    }
}

void HistoryLogger::destoryInstance()
{
    if (_instance)
    {
        delete _instance;
        _instance = nullptr;
    }
}

record HistoryLogger::createRecord(char* type, std::string text, std::string name, Color4B color)
{
    recordType tmpType;
    switch (type)
    {
        case "null":
            tmpType = recordType::null;
            break;
        case "talk":
            tmpType = recordType::talk;
        case "select":
            tmpType = recordType::select;
        default:
            tmpType = recordType::null;
            break;
    }
    record tmpRecord = new record(tmpType, text, name, color);
}

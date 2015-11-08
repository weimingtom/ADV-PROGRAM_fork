#include "SCIf.h"
#include "GameSystem.h"
#include <sstream>


ScriptReader::SCIf::SCIf(ScriptReader *reader, std::string expression, std::string trueTag, std::string falseTag)
	: _expression(expression)
	, _trueTag(trueTag)
	, _falseTag(falseTag)
{
	this->reader = reader;
	this->type = ScriptCommandType::If;
}


ScriptReader::SCIf::~SCIf()
{
}

void ScriptReader::SCIf::execute(cocos2d::Node* stage)
{
	if (_expression.compare("") == 0)
	{
		cocos2d::log("SC> If expressiong is null");
		reader->nextScript();
	}
	if (expressionJudge())
	{
		//cocos2d::log("SC> If (%s) is true, jump to %s", _expression.c_str(), _trueTag.c_str());
		jump(_trueTag);
	}
	else
	{
		//cocos2d::log("SC> If (%s) is false, jump to %s", _expression.c_str(), _falseTag.c_str());
		jump(_falseTag);
	}
	
}

//#If:key>1:gameStart -> key>1
bool ScriptReader::SCIf::expressionJudge()
{
	int pos;
	std::string exp = _expression;
	pos = exp.find_first_of("><=", 0);
	if (pos < 0)
	{
		cocos2d::log("SC> If expressiong do not have symbol");
		return true;
	}
	else
	{
		std::string sFirstValue;
		std::string sSecondValue;
		int iFirstValue;
		int iSecondValue;
		std::stringstream ssFirstValue;
		std::stringstream ssSecondValue;

		//从表达式中提取第一个值
		sFirstValue = exp.substr(0, pos);
		if ((exp[0] >= '0') && (exp[0] <= '9'))	//当第一个值是常数
		{
			ssFirstValue << sFirstValue;
			ssFirstValue >> iFirstValue;
		}
		else //当第一个值是变量
		{
			iFirstValue = GameSystem::getInstance()->getDataValue(sFirstValue);
		}

		//判断符号
		if (exp[pos] == '>')	//大于的情况下
		{
			if (exp[pos + 1] == '=')	//大于等于的情况下
			{
				//从表达式中提取第二个值
				sSecondValue = exp.substr(pos + 2, exp.length() - 1);
				if ((exp[pos + 3] >= '0') && (exp[pos + 3] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}
				
				if (iFirstValue >= iSecondValue)
					return true;
				else
					return false;
			}
			else
			{
				sSecondValue = exp.substr(pos + 1, exp.length() - 1);
				if ((exp[pos + 2] >= '0') && (exp[pos + 2] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}

				if (iFirstValue > iSecondValue)
					return true;
				else
					return false;
			}
		}
		else if (exp[pos] == '<')	//小于的情况下
		{
			if (exp[pos + 1] == '=')	//小于等于的情况下
			{
				sSecondValue = exp.substr(pos + 2, exp.length() - 1);
				if ((exp[pos + 3] >= '0') && (exp[pos + 3] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}

				if (iFirstValue <= iSecondValue)
					return true;
				else
					return false;
			}
			else
			{
				sSecondValue = exp.substr(pos + 1, exp.length() - 1);
				if ((exp[pos + 2] >= '0') && (exp[pos + 2] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}

				if (iFirstValue < iSecondValue)
					return true;
				else
					return false;
			}

		}
		else if (exp[pos] == '=')	//相等的情况下
		{
			sSecondValue = exp.substr(pos + 2, exp.length() - 1);
			if ((exp[pos + 3] >= '0') && (exp[pos + 3] <= '9'))
			{
				ssSecondValue << sSecondValue;
				ssSecondValue >> iSecondValue;
			}
			else
			{
				iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
			}

			if (iFirstValue == iSecondValue)
				return true;
			else
				return false;
		}

	}
}

void ScriptReader::SCIf::jump(std::string tag)
{
	if (tag.compare("") == 0)
	{
		reader->nextScript();
		return;
	}
	else
	{
		reader->jumpToSign(tag);
	}
}
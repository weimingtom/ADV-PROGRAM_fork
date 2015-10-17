﻿#include "ScriptReader.h"
//#include "ScriptCommand.h"
#include "SCCharactorSpeak.h"
#include "SCLeave.h"
#include "SCJump.h"
#include "SCSelect.h"
#include "SCBackground.h"
#include "SCPlayBGM.h"
#include "SCStopBGM.h"
#include "SCPlaySound.h"
#include "SCStopSound.h"
#include "SCSet.h"
#include "CharactorManager.h"
#include "GameSystem.h"

USING_NS_CC;

ScriptReader::ScriptReader()
	:_currentSignName("gameStart")
	, _currentCommandIndex(0)
	, nextPositionIsLeft(true)
	, charNumber(0)
	, stage(nullptr)
{
}


ScriptReader::~ScriptReader()
{
	clearScript();
	delete(chars);
}

void ScriptReader::initWithStage(Node* stage)
{
	this->stage = stage;
	charStage = Layer::create();
	stage->addChild(charStage);
	for (int i = 0; i < 5; i++)
	{
		chars[i] = nullptr;
	}
	
	log("init ending");

}

/*
清理数据
对于命令行，因为是用父类声明，所以不能直接delete，需要转换为子类，再delete。不然子类的字段不会被释放
*/

void ScriptReader::clearScript()
{
	for (auto itr = _scripts.begin(); itr != _scripts.end(); itr++)
	{
		auto list = itr->second;
		int size = list->size();
		("DeleteList size[%d]", size);
		if (size > 0)
		{
			for (int i = 0; i < size; i++)
			{
				auto ptr = list->at(i);
				switch (ptr->type)
				{
				case ScriptCommandType::CharactorSpeak:
					delete (SCCharactorSpeak*)ptr;
					break;
				}
				//↑待填补

			}
		}
		list->clear();
		delete list;
	}
	_scripts.clear();
	isWaitingForSelection = false;
}

void ScriptReader::loadScriptFile(std::string path)
{
	clearScript();

	std::string ss = FileUtils::getInstance()->getStringFromFile(path);

	int sPos = 0;
	int ePos = 0;

	std::string currentSign = "default";	//标签，默认default
	auto cms = new std::vector<ScriptCommand*>();
	_scripts.insert(std::pair<std::string, std::vector<ScriptCommand*>*>(currentSign, cms));

	log("LoadScript::>");

	SCSelect* currentSelect = nullptr;

	while (sPos >= 0)
	{
		log("load succeess");
		ePos = ss.find('\n', sPos);	//从脚本中读出一行
		std::string command;	//储存解读脚本命令
		if (ePos < 0)
		{
			command = ss.substr(sPos, ss.length() - sPos);
			sPos = -1;
		}
		else
		{
			command = ss.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
		}

		if (command.length() > 1 && !command.empty())
		{
			if (command[0] == '/'){}	//解读为注释，忽略该行
			else
			{
				if (command[0] == '@')
				{
					//解读为记录脚本段落
					//currentSelect = nullptr;
					//log("Sign[%s] Size[%d]", currentSign.capacity(), cms->size());
					currentSign = command.substr(1, command.length() - 1);
					cms = new std::vector<ScriptCommand*>();
					_scripts.insert(std::pair < std::string, std::vector<ScriptCommand*>*>(currentSign,cms));
					log("SC> Add sign[%s]", currentSign.c_str());
				}
				else
				{
					if (command[0] == '#')	//解读脚本命令
					{
						std::string cmd = command.substr(1, command.length() - 1);
						int scriptNamePos = cmd.find_first_of(':', 0);
						std::string cmdParams = "";
						if (scriptNamePos > 0)
						{
							cmdParams = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
							cmd = cmd.substr(0, scriptNamePos);
						}
						log("SC> Add command[%s] params[%s] Sign[%s]", cmd.c_str(), cmdParams.c_str(), currentSign.c_str());

						if (cmd.compare("Select") == 0)
						{
							SCSelect* selectCMD = new SCSelect(this);
							currentSelect = selectCMD;
							cms->push_back(selectCMD);
						}
						else
							if (cmd.compare("GameOver") == 0)
							{
								//游戏结束，待补充
							}
							else
								if (cmd.compare("Leave") == 0)
								{
									SCLeave* leaveCMD = new SCLeave(this, cmdParams);
									cms->push_back(leaveCMD);
								}
								else
									if (cmd.compare("Set") == 0)
									{
										std::string key;
										char mark;
										int value;
										int pos;
										pos = cmdParams.find_first_of("+-=", 0);
										key = cmdParams.substr(0, pos);
										mark = cmdParams[pos];
										cmdParams.substr(pos + 1, cmdParams.length() - 1);
										pos = cmdParams.find_first_of("+-", 0);
										log("Setttttt add!");
										if (pos < 0)
										{
											log("Setttttt add 2!");
											value = atoi(cmdParams.c_str());
										}
										else
										{
											log("Setttttt add 3!");
											char tmpChar = cmdParams[pos];
											std::string tmpString;
											switch (tmpChar)
											{
											case '-':
												value = 1;
												//value = GameSystem::getInstance()->getDataValue(cmdParams.substr(0, pos));// -atoi(cmdParams.substr(pos + 1, cmdParams.length() - 1).c_str());
												break;
											case '+':
												//value = GameSystem::getInstance()->getDataValue(cmdParams.substr(0, pos));// +atoi(cmdParams.substr(pos + 1, cmdParams.length() - 1).c_str());
												value = 1;
												break;
											default:
												break;
											}
										}
										log("Set Add!");
										SCSet* setCMD = new SCSet(this, key, mark, value);
										cms->push_back(setCMD);
									}
									else
										if (cmd.compare("Jump") == 0)
										{
											SCJump* jumpCMD = new SCJump(this, cmdParams);
											cms->push_back(jumpCMD);
										}
										else
											if (cmd.compare("Background") == 0)
											{
												SCBackground* backgroundCMD = new SCBackground(this, cmdParams);
												cms->push_back(backgroundCMD);
											}
											else
												if (cmd.compare("PlayBGM") == 0)
												{
													SCPlayBGM* playBGMCMD = new SCPlayBGM(this, cmdParams);
													cms->push_back(playBGMCMD);
												}
												else
													if (cmd.compare("StopBGM") == 0)
													{
														SCStopBGM* stopBGMCMD = new SCStopBGM(this);
														cms->push_back(stopBGMCMD);
													}
													else
														if (cmd.compare("PlaySound") == 0)
														{
															SCPlaySound* playSoundCMD = new SCPlaySound(this, cmdParams);
															cms->push_back(playSoundCMD);
														}
														else
															if (cmd.compare("StopSound") == 0)
															{
																SCStopSound* stopSoundCMD = new SCStopSound(this);
																cms->push_back(stopSoundCMD);
															}
															else
										{
											log("Unknow Script Command> [%s]:[%s]", cmd.c_str(), cmdParams.c_str());
										}
					}
					else
					{
						if (command[0] == '>')	//解读选择项
						{
							if (currentSelect != nullptr)
							{
								std::string cmd = command.substr(1, command.length() - 1);
								int scriptNamePos = cmd.find_first_of(':', 0);
								std::string cmdParams = "";
								if (scriptNamePos > 0)
								{
									cmdParams = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
									cmd = cmd.substr(0, scriptNamePos);
								}
								log("SC> options Sign[%s] text[%s]", cmd.c_str(), cmdParams.c_str());
								currentSelect->addOption(cmd, cmdParams);
							}
						}
						else
						{
							//对话
							std::string cmd = command;//记录人名部分
							int scriptNamePos = cmd.find_first_of(':', 0);
							std::string cmdParams = "";
							if (scriptNamePos > 0)
							{
								cmdParams = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
								cmd = cmd.substr(0, scriptNamePos);
							}
							scriptNamePos = cmd.find_first_of('#', 0);
							std::string face = "";
							if (scriptNamePos > 0)
							{
								face = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
								cmd = cmd.substr(0, scriptNamePos);
							}
							log("SC Csay CHA[%s] Face[%s] Text[%s]", cmd.c_str(), face.c_str(), cmdParams.c_str());
							SCCharactorSpeak* csCMD = new SCCharactorSpeak(this, cmd, cmdParams, face);
							cms->push_back(csCMD);
						}
					}
				}
			}
		}
	}

}

void ScriptReader::jumpToSign(std::string &sign)
{
	isWaitingForSelection = false;
	auto list = _scripts.find(sign);
	if (list == _scripts.end())
	{
		log("Sign [%s] not found", sign.c_str());
		return;
	}
	_currentSignName = sign;
	_currentCommandIndex = 0;
	nextScript();
}

void ScriptReader::nextScript()
{
	log("loading");
	if (isWaitingForSelection)
	{
		log("waitting");
		return;
	}
	auto list = _scripts.find(_currentSignName);
	if (list == _scripts.end())
	{
		log("No Sign of currentSign [%s]", _currentSignName.c_str());
		return;
	}
	auto cmdList = list->second;
	if (_currentCommandIndex >= (int)cmdList->size())
	{
		log("End of Script..! CurrentScript");
	}

	auto cmd = cmdList->at(_currentCommandIndex);

	switch (cmd->type)
	{
	case ScriptCommandType::CharactorSpeak:
		((SCCharactorSpeak*)cmd)->execute(stage);
		break;
	case ScriptCommandType::Leave:
		((SCLeave*)cmd)->execute(stage);
		break;
	case ScriptCommandType::Jump:
		((SCJump*)cmd)->execute(stage);
		break;
	case ScriptCommandType::Select:
		((SCSelect*)cmd)->execute(stage);
		break;
	case ScriptCommandType::Background:
		((SCBackground*)cmd)->execute(stage);
		break;
	case ScriptCommandType::PlayBGM:
		((SCPlayBGM*)cmd)->execute(stage);
		break;
	case ScriptCommandType::StopBGM:
		((SCStopBGM*)cmd)->execute(stage);
		break;
	case ScriptCommandType::PlaySd:
		((SCPlaySound*)cmd)->execute(stage);
		break;
	case ScriptCommandType::StopSd:
		((SCStopSound*)cmd)->execute(stage);
		break;
	case ScriptCommandType::Set:
		((SCSet*)cmd)->execute(stage);
		break;
	default:
		log("Unhandle ScriptCommandType [%d]", cmd->type);
	}
	_currentCommandIndex++;
}
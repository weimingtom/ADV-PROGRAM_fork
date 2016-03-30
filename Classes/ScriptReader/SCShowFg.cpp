//
//  SCShowFg.cpp
//  Karma
//
//  Created by 古东珲 on 16/3/29.
//
//

#include "SCShowFg.hpp"
#include "CharactorManager.h"

ScriptReader::SCShowFg::SCShowFg(ScriptReader* reader, std::string &name, std::string &face)
:name(name),face(face)
{
    this->reader = reader;
    this->type = ScriptCommandType::ShowFg;
}

ScriptReader::SCShowFg::~SCShowFg()
{
    
}

void ScriptReader::SCShowFg::execute(cocos2d::Node *stage)
{
    Charactor* cha = nullptr;
    cha = CharactorManager::getInstance()->getCharactor(name);
    cha->getCharactorFace(face);
}
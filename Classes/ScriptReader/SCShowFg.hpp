//
//  SCShowFg.hpp
//  Karma
//
//  Created by 古东珲 on 16/3/29.
//
//

#ifndef SCShowFg_hpp
#define SCShowFg_hpp

#include "ScriptReader.h"
#include "ScriptCommand.h"

//enum CharactorFaceType;

class ScriptReader::SCShowFg :public ScriptCommand
{
public:
    std::string name;
    std::string face;
    
    SCShowFg(ScriptReader *reader, std::string &name, std::string &face);
    
    ~SCShowFg();
    
    void execute(cocos2d::Node* stage);
    
    
};

#endif /* SCShowFg_hpp */

#pragma once

#include "cocos2d.h"

using namespace cocos2d;


class TestLayer:public Layer{

    bool init();

    std::map<std::string,Node*> testMap;
    
    public :
    
    CREATE_FUNC(TestLayer);
    
};
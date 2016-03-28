#include "TestLayer.h"
#include "TestFolder/TestInFolder.h"

bool TestLayer::init(){
    if(!Layer::init()){
        return false;
    }

    auto lb=Label::createWithSystemFont("TEST", "MSYH.ttf", 24);
    addChild(lb);
    
    
    testMap.insert(std::pair<std::string,Node*>("nod",lb));
    TestInFolder test;
    test.build();
    
    return true;
}

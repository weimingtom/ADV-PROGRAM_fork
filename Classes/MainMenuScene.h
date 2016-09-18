#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
    //--绘制下雨效果--
    cocos2d::DrawNode* drawNode;
    
    void update(float dt);
    
    struct Rain{
        float x;
        float y;
        float landLen;
        float len;
        float alpha;
        bool isLand;
    };
    
    struct RainOver{
        float x;
        float y;
        float r;
        float alpha;
    };
    
    std::vector<Rain*> rains;
    std::vector<RainOver*> rainOvers;
    
    void appendRain();
    //--------------
public:
    MainMenu();
	~MainMenu();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenu);

	void test();

	void menuExit(Ref* pSender);

	void newgame();	//进入新游戏
	void config();	//游戏设置
	void load();	//读取存档

};

#endif
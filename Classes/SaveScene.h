#ifndef SAVESCENE_H
#define SAVESCENE_H
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class SaveScene : public Layer
{
	SaveData* dataButtons[8];
	EventListenerTouchOneByOne* eventTouch[8];
    int _currentSelectButton;
public:
	SaveScene();
	~SaveScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SaveScene);

	void back();	//返回
    
    void popup();    //弹出对话
    
    void apply();    //对话窗按下Yes
    
    void cancel();   //对话窗按下No
};

#endif
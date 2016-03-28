#ifndef SAVESCENE_H
#define SAVESCENE_H
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class SaveScene : public Layer
{
	SaveData* dataButtons[8];
	EventListenerTouchOneByOne* eventTouch[8];
public:
	SaveScene();
	~SaveScene();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SaveScene);

	void back();	//����

	void save(int i);	//�浵
};

#endif
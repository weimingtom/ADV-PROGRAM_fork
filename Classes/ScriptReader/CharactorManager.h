#ifndef __CHARATOR_MANAGER_H__
#define __CHARATOR_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

#define CM CharactorManager::getInstance()


//立绘位置
enum PositionType
{
	EMPTY,	//没有位置
	LEFT,	//左边
	LEFT_CENTER,	//左中
	CENTER,	//中间
	RIGHT_CENTER,	//右中
	RIGHT
};


/*
角色信息
*/
struct Charactor
{
	std::string key;	//角色key
	std::string name;	//角色名
	Color3B color;	//对白颜色（暂时不使用）
	//待补充……
	std::map<std::string, char*>* fgList;	//立绘列表
	int favor;	//好感度（暂时不使用）
	int hate;	//仇恨度（暂时不使用）

	Sprite* faceSprite;	//当前显示中的精灵，考虑到角色入场和离场所使用的存储的变量。
	std::string currentFace;	//当前显示的立绘
	bool positionIsLeft;	//显示的位置
	PositionType currentPosition;	//当前显示的位置

	Charactor()
		:name("NoName")
		, color(Color3B::BLACK)
		//待补充……
		, fgList(nullptr)
		, favor(0)
		, hate(0)
		, faceSprite(nullptr)
		, currentFace("")
	{
        fgList = new std::map<std::string, char*>;
    }

	char* getCharactorFace(std::string &face)	//根据face值获取角色表情
	{
		// log("CM> result.first = %s", face.c_str());
        auto result = fgList->find(face);
		if (result != fgList->end())
		{
			// log("CM> result.second = %s", result->second);
			return result->second;
		}
		else
		{
			return nullptr;
		}
	}

	void moveTo(PositionType pt)
	{
		int Distance;	//立绘移动的位置
		//auto actionTo = MoveTo::create(1, Point(Distance, 0));
		switch (pt)
		{
		case PositionType::LEFT:
		{
			//faceSprite->setPositionX(320);
            setAction(320);
			break;
		}
		case PositionType::LEFT_CENTER:
		{
			//faceSprite->setPositionX(427);
            setAction(427);
			break;
		}
		case PositionType::CENTER:
		{
			//faceSprite->setPositionX(640);
			setAction(640);
			break;
		}
		case PositionType::RIGHT_CENTER:
		{
			//faceSprite->setPositionX(853);
            setAction(853);
			break;
		}
		case PositionType::RIGHT:
		{
			//faceSprite->setPositionX(960);
            setAction(960);
			break;
		}
		default:
		{
			log("[Error]CM> Unknow PositionType.");
			break;
		}
		}
		currentPosition = pt;
	}
    
    void setAction(int Distance)
    {
        auto mtAction = MoveTo::create(0.3f,Point(Distance,0));
        mtAction->setTag(1);
        faceSprite->runAction(MoveTo::create(0.3f, Point(Distance, 0)));
    }

	void leave()
	{
		if (faceSprite)
		{
            log("%s is leaving.",name.c_str());
			faceSprite->removeFromParent();
			faceSprite = nullptr;
			currentFace = "";
			currentPosition = PositionType::EMPTY;
		}
	}
};

/*
角色管理类。
管理角色数据。
通过getInstance获取Managet实例
不使用时，需要调用destoryInstance进行销毁
*/
class CharactorManager
{
	static CharactorManager* _instance;

	CharactorManager();
	~CharactorManager();
	
	std::map<std::string, Charactor*> *_pool;	//配置文件列表。<角色key，角色对象>

	Charactor *defaultCharactor;	//脚本出现的角色未定义则使用默认角色
public:
	static CharactorManager* getInstance();
	static void destoryInstance();

	Charactor* getCharactor(std::string &key);	//根据Key值获取角色对象

	void addCharactor(std::string &key, Charactor* cha);	//存储角色信息
};

#endif


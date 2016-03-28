#include "HelloWorldScene.h"

//#include "TestLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World!!!", "fonts/Marker Felt.ttf", 24);
	auto label2 = Label::createWithTTF("Change the world!", "fonts/Marker Felt.ttf", 28);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height - 30));
	
    // add the label as a child to this layer
    this->addChild(label, 1);
	this->addChild(label2, 2);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
	//auto Junyu = Sprite::create("IMG_4656.JPG");
	//auto TestButton = MenuItemImage::create("IMG_5226.JPG", "IMG_5226.JPG",CC_CALLBACK_1(HelloWorld::menuTestButton, this));

    // position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//Junyu->setScale(0.25);
	//Junyu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//TestButton->setPosition(Vec2(200, 200));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	//this->addChild(Junyu, 1);
	//this->addChild(TestButton, 2);
    
	//auto TestMenu = Menu::create(TestButton, NULL);
	//TestMenu->setPosition(Vec2::ZERO);
	//this->addChild(TestMenu, 2);
    
    //auto ly=TestLayer::create();
    //addChild(ly);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuTestButton(Ref* pSender)
{
	auto Power = Sprite::create("IMG_5401.JPG");
	Power->setScale(0.125);
	Power->setPosition(100, 100);
	this->addChild(Power, 3);
}
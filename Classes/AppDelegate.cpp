#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
//#include "GameScene.h"
//#include "TestLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if CC_TARGET_PLATFORM==CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM==CC_PLATFORM_MAC
		glview = GLViewImpl::createWithRect("Karma Beta 0.0725", Rect(0, 0, 1136, 640));
#else 
        glview = GLViewImpl::create("Karma Beta 0.0725");
#endif
        director->setOpenGLView(glview);
		//改变窗口大小和自适应策略
		glview->setFrameSize(1136, 640);
		glview->setDesignResolutionSize(1136, 640, kResolutionShowAll);
        //glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
        
    }
    glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	auto mainScene = MainMenu::createScene();
    // auto scene = TestLayer::create();

    // run 进入游戏时候首先显示哪个场景
    //director->runWithScene(scene);
    director->runWithScene(mainScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

/*
extern "C"
{
    size_t fwrite$UNIX2003(const void *a, size_t b, size_t c, FILE *d)
    {
        return fwrite(a, b, c, d);
    }
    char* strerror$UNIX2003(int errnum)
    {
        return strerror(errnum);
    }
}
 */

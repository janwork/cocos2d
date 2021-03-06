#include "AppDelegate.h"
#include "MenuScene.h"
#include"SimpleAudioEngine.h"   //包含声音引擎头文件  
#include "AppMacros.h"
#include "AppCommon.h"

USING_NS_CC;
using namespace CocosDenshion;//使用该声音引擎的命名空间  

AppDelegate::AppDelegate()
{

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
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// 初始化Director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview)
	{
		glview = GLViewImpl::create("doudizhu");
		// 960 540
		//glview->setFrameSize(1200,675);
		director->setOpenGLView(glview);

		glview->setFrameSize(1200, 675);
		//glview->setDesignResolutionSize(1200,675, ResolutionPolicy::FIXED_WIDTH);
		glview->setDesignResolutionSize(1200, 675, ResolutionPolicy::SHOW_ALL);

	}

	//director->setContentScaleFactor(SCALE_FACTOR);

	// 设置帧数
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);

	// 加载游戏需要资源
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("poker_b.plist", "poker_b.png");
	frameCache->addSpriteFramesWithFile("gameover/ddzsingle_map_lvl.plist", "gameover/ddzsingle_map_lvl.png");
	frameCache->addSpriteFramesWithFile("gameover/nt_result_base.plist", "gameover/nt_result_base.png");

	// 运行菜单场景
	auto scene = MenuScene::createScene();
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

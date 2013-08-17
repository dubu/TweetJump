#include "AppDelegate.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "MainScene.h"
#include "GameScene.h"
#include "AppMacros.h"

using namespace cocos2d;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    // Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

	CCSize frameSize = pEGLView->getFrameSize();
    vector<string> searchPath;

	// ONLY iPhone resources provided
    searchPath.push_back(smallResource.directory);
	
//	CCFileUtils::sharedFileUtils()->setResourceDirectory(smallResource.directory);
    pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);

    // set searching path
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	// turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	CCScene *pScene = CCScene::create();
	pScene->addChild(GameScene::create());

	pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

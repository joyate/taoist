#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "frame/GameScene.h"

#include "game_ui/Loading.h"


// test
//#include "HelloWorldScene.h"
//#include "BattleScene.h"
//#include "GameData.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);


#ifdef __WIN_DEV__
	glview->setFrameSize(1280,720);
	//glview->setFrameSize(1920,1080);
#endif

	Size design_size(1280,720);
	
	// factor should be resource width/height contrast design width/height
	float factor = glview->getFrameSize().width/design_size.width;
	//director->setContentScaleFactor(factor);
	glview->setDesignResolutionSize(design_size.width,design_size.height,ResolutionPolicy::FIXED_HEIGHT);


	std::vector<std::string> search_paths;
	search_paths.push_back("game_res");
	search_paths.push_back("game_res/map");
	search_paths.push_back("game_res/obj");
	search_paths.push_back("fonts");
	search_paths.push_back("game_res/ui");
	FileUtils::getInstance()->setSearchPaths(search_paths);


	int time_summy;
	srand((unsigned int)&time_summy);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = SceneMain::create();
	auto scene = Loading::create();
	if(!scene->initConfig())
	{	
		CCLOG("init config failed");
		return false;
	}
	if(!scene->initTargetSceneId(SceneMain::SCENE_ID))
	{
		CCLOG("initTargetSceneId failed");
		return false;	
	}

	// run
	director->runWithScene(scene);
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

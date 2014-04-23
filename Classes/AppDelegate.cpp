#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "OpeningLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();
    

    director->setOpenGLView(eglView);
	
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
    
    // とりあえずiPhone4S以上対応なので解像度系はiphone5で対応
    Resource res  = iphone5;
    std::vector<std::string> searchPath;
    searchPath.push_back(res.directory);
    auto fileutil = FileUtils::getInstance();
    fileutil->setSearchResolutionsOrder(searchPath);
    eglView->setDesignResolutionSize(res.size.width, res.size.height, ResolutionPolicy::FIXED_WIDTH);
    director->setContentScaleFactor(res.scaleFactor);
    
    // ccbiのロード
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("OpeningLayer", OpeningLayerLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("Opening.ccbi");
    Scene* scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

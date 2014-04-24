//
//  BetScene.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#ifndef __Casidra__BetScene__
#define __Casidra__BetScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Params.h"
#include <array>
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_BUTTON_NUM 6
#define MAX_PAGE_NUM 16

class BetScene : public Layer
, public CCBSelectorResolver
{
private:
    void _updateView(Type::BetScenePage pageType);
    void _clearView();
    void _addNumericEditBox();
    void _setUpEditBox(const char* placeHolder);
    
public:
    BetScene();
    virtual ~BetScene();
    void initScene(); // ccbiをreadした後によぶこと！
    
    CC_SYNTHESIZE_READONLY(Type::BetScenePage, _currentPageType,  CurrentPageType);
    CC_SYNTHESIZE_READONLY(Type::BetScenePage, _nextPageType,     NextPageType);
    CC_SYNTHESIZE_READONLY(Type::BetScenePage, _previousPageType, PreviousPageType);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName);
    void tappedPreviousButton(Object* pSender, Control::EventType pControlEventType);
    void tappedNextButton(    Object* pSender, Control::EventType pControlEventType);
    void tappedSelectButton(Object* pSender,   Control::EventType pControlEventType);
    void tappedHatenaButton(Object* pSender,   Control::EventType pControlEventType);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BetScene, create);
};

//
// Loader
//
class BetSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BetSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BetScene);
};


#endif /* defined(__Casidra__BetScene__) */

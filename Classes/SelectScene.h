//
//  SelectScene.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#ifndef __Casidra__SelectScene__
#define __Casidra__SelectScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Params.h"
#include <array>
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_BUTTON_NUM 6
#define MAX_PAGE_NUM 16

class SelectScene : public Layer
, public CCBSelectorResolver
{
private:
    void _updateView(Type::SelectScenePageType pageType);
    void _clearView();
    void _addNumericEditBox();
    void _setUpEditBox(const char* placeHolder);
    
public:
    SelectScene();
    virtual ~SelectScene();
    void initScene(Type::SelectScenePageType pageType); // ccbiをreadした後によぶこと！
    void initScene(Type::SelectScenePageType pageType, int slotId);
    
    CC_SYNTHESIZE_READONLY(Type::SelectScenePageType, _currentPageType,  CurrentPageType);
    CC_SYNTHESIZE_READONLY(Type::SelectScenePageType, _nextPageType,     NextPageType);
    CC_SYNTHESIZE_READONLY(Type::SelectScenePageType, _previousPageType, PreviousPageType);
    CC_SYNTHESIZE_READONLY(int, _targetSlotId, TargetSlotId);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName);
    void tappedPreviousButton(Object* pSender, Control::EventType pControlEventType);
    void tappedNextButton(    Object* pSender, Control::EventType pControlEventType);
    void tappedSelectButton(Object* pSender,   Control::EventType pControlEventType);
    void tappedHatenaButton(Object* pSender,   Control::EventType pControlEventType);
    void replaceSceneToBetScene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectScene, create);
};

//
// Loader
//
class SelectSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectScene);
};


#endif /* defined(__Casidra__SelectScene__) */

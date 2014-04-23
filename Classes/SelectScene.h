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
#include <array>

USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_BUTTON_NUM 6
#define MAX_PAGE_NUM 16

class SelectScene : public Layer
, public CCBSelectorResolver
//, public CCBMemberVariableAssigner
{
// var
private:
    enum NodeTag {
        Header    = 10,
        Footer     = 11,
        TitleLabel = 12,
        ButtonNode    = 20,
        
        SelectButton = 0,
        HatenaButton =1,
    };
    
    enum PageType {
        SelectRouletteType,
        SelectMethod,
        SelectZone,
        InputMinBet,
    };
    
    CC_SYNTHESIZE_READONLY(PageType, _currentPageType, CurrentPageType);
    
public:
    //CC_SYNTHESIZE_READONLY(CCBAnimationManager*, _animationManager, AnimationManager);
    //CC_SYNTHESIZE_READONLY(Node*, _SelectSceneNode, SelectSceneNode);
    
    //virtual bool onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName);
    //virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName);
    void tappedSelectButton(Object* pSender, Control::EventType pControlEventType);
    void tappedHatenaButton(Object* pSender, Control::EventType pControlEventType);
    
// func
private:
    void _updateView();
    void _updateTitleLabel();
    void _updateSelectButton();
    
public:
    SelectScene();
    virtual ~SelectScene();
    
    //CC_SYNTHESIZE(int, _selectedStageID, SelectedStageID);
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectScene, create);
    
    void initScene(); // ccbiをreadした後によぶこと！
    //void updatePointBar( float dt );
    /*void startMainSceneCallback();
    void startAIGameSceneCallback(int stageID);
    void startTutorialSceneCallback();
    void setAnimationManager(CCBAnimationManager* pAnimationManager);

    void doneNextPageCallback(Node* sender);
    void donePreviousPageCallback(Node* sender);
    void finishBattleStartAnim(Node* sender);*/

private:
    //virtual void onEnter();
    /*
    void _setPointLabel();
    void _setPointBarScale();
    void _updateView();
    void _updateStage(int relateivPageID, int column, int currentWorld);
    void _updatePageView(int currentPage);
    void _updateStageView(int currentPage);
    int _getStageID(int worldNo, int stageNo);
    int _getWorldNo(int stageID);
    void _setUnlocked(Node* stageNode);
    void _setLocked(Node* stageNode);
    void _setCurrent(Node* stageNode);
    void _setStageText(int stageID, Node* stageNode);
    bool _calcPointConsumption( int column );
    bool _canPlayGame();
    void _setSelectSceneTuchEnable(bool isEnable);
     */
};

class SelectSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectScene);
};


#endif /* defined(__Casidra__SelectScene__) */

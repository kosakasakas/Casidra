//
//  SelectScene.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#include "SelectScene.h"
#include "Utility.h"
#include "Params.h"
#include "NodeTag.h"
#include "AudioManager.h"
#include "GameController.h"
/*#import "MainMenuLayer.h"
#import "GameLayer.h"
#import "GameComponentLayer.h"
#import "AudioManager.h"
#import "TutorialLayer.h"*/

USING_NS_CC;


SelectScene::SelectScene()
:_currentPageType(SelectRouletteType)
{
}

SelectScene::~SelectScene()
{
    /*CC_SAFE_RELEASE(stagePointLabel);
    CC_SAFE_RELEASE(stagePointBarSprite);
    CC_SAFE_RELEASE(_SelectSceneNode);*/
}
/*
void SelectScene::onEnter() {
    Layer::onEnter();
    //AudioManager::playBackGroundMusic(AudioManager::startBgmFile);
}

bool SelectScene::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "stagePointLabel", LabelTTF*, stagePointLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "stagePointBarSprite", Sprite*, stagePointBarSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_SelectSceneNode", Node*, _SelectSceneNode);

    return true;
}*/
/*
SEL_CallFuncN SelectScene::onResolveCCBCCCallFuncSelector(cocos2d::Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "doneNextPageCallback", SelectScene::doneNextPageCallback);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "donePreviousPageCallback", SelectScene::donePreviousPageCallback);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "finishBattleStartAnim", SelectScene::finishBattleStartAnim);
    return NULL;
}*/

SEL_MenuHandler SelectScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOGERROR("name_menu_item = %s", pSelectorName);
    
    return NULL;
}

Control::Handler SelectScene::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name_control = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedPreviousButton", SelectScene::tappedPreviousButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedNextButton", SelectScene::tappedNextButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSelectButton", SelectScene::tappedSelectButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedHatenaButton", SelectScene::tappedHatenaButton);
    return NULL;
}
/*
void SelectScene::doneNextPageCallback(Node* sender) {
    _currentPage++;
    _updateView();
}

void SelectScene::donePreviousPageCallback(Node* sender) {
    _currentPage--;
    _updateView();
}
*/

void SelectScene::initScene() {
    // update funcをスケジュールに登録
    _updateView(SelectScene::SelectRouletteType);
    addNumericEditBox();
}

/*
void SelectScene::updatePointBar(float dt)
{
    if(stagePointLabel) _setPointLabel();
    if(stagePointBarSprite) _setPointBarScale();
}
*/

void SelectScene::_updateView(SelectScene::PageType pageType){
    auto title = (LabelTTF*) this->getChildByTag(NodeTag_SelectScene::Header)->getChildByTag(NodeTag_Header::TiteLabel);
    auto desc  = (LabelTTF*) this->getChildByTag(NodeTag_SelectScene::TitleLabel);
    
    const char* titleTex;
    const char* descTex;
    const char** buttonTexList;
    int elementNum;
    
    if(pageType == SelectRouletteType) {
        titleTex = Text_SelectScene::title_rouletteType;
        descTex  = Text_SelectScene::desc_rouretteType;
        buttonTexList = Text_List::rouletteType;
        elementNum    = Type::RouletteTypeNum;
    } else if (pageType == SelectMethod) {
        titleTex = Text_SelectScene::title_betMethod;
        descTex  = Text_SelectScene::desc_betMethod;
        buttonTexList = Text_List::method;
        elementNum    = Type::MethodNum;
    } else if (pageType == SelectMinBet) {
        titleTex = Text_SelectScene::title_minBet;
        descTex  = Text_SelectScene::desc_minBet;
    } else if (pageType == SelectZone) {
        titleTex = Text_SelectScene::title_betZone;
        descTex  = Text_SelectScene::desc_betZone;
        buttonTexList = Text_List::zone;
        elementNum    = Type::ZoneNum;
    } else {
        titleTex = "none";
        descTex  = "node";
        buttonTexList = NULL;
        elementNum    = 0;
    }
    
    title->setString(titleTex);
    desc->setString(descTex);
    if(buttonTexList != NULL) {
        for (int i = 0; i < MAX_BUTTON_NUM; i++) {
            auto buttonNode = this->getChildByTag(NodeTag_SelectScene::ButtonNode+i);
            auto button = (ControlButton*) buttonNode->getChildByTag(NodeTag_SelectScene::SelectButton);
            auto hatena = (ControlButton*) buttonNode->getChildByTag(NodeTag_SelectScene::HatenaButton);
            auto label = (LabelTTF*) buttonNode->getChildByTag(NodeTag_SelectScene::ButtonLabel);
            if (i < elementNum) {
                label->setString(buttonTexList[i]);
                button->setVisible(true);
                hatena->setVisible(true);
            } else {
                label->setString("");
                button->setVisible(false);
                hatena->setVisible(false);
            }
        }
    }
}

/*
void SelectScene::_updatePageView(int currentPage) {
    if(currentPage == 0) {
        this->getChildByTag(PreviousPageButton)->setVisible(false);
        this->getChildByTag(NextPageButton)->setVisible(true);
    } else if(currentPage == WORLD_NUM-1) {
        this->getChildByTag(NextPageButton)->setVisible(false);
        this->getChildByTag(PreviousPageButton)->setVisible(true);
    } else {
        this->getChildByTag(NextPageButton)->setVisible(true);
        this->getChildByTag(PreviousPageButton)->setVisible(true);
    }
    
    auto pageBlock = this->getChildByTag(PageBlockNode);
    for (int i = 0; i < WORLD_NUM; i++){
        LayerColor* block = (LayerColor*) pageBlock->getChildByTag(i);
        if (currentPage == i) {
            block->setColor(Color3B(100,100,255));
        } else {
            block->setColor(Color3B(0,0,0));
        }
    }
}

void SelectScene::_updateStageView(int currentPage) {
    for ( int relativePageID = 0; relativePageID < 3; relativePageID++ ) {
        for ( int column = 0; column < STAGE_NUM; column++ ) {
            _updateStage(relativePageID, column, currentPage);
        }
    }
}

void SelectScene::_updateStage(int relateivPageID, int column, int currentPage) {
    auto stageLayer = this->getChildByTag(StageLayerNode);
    auto pageNode  = stageLayer->getChildByTag(PageNode+relateivPageID);
    auto stageNode = pageNode->getChildByTag(StageNode+column);
    auto userData = UserData::getInstance();
    
    int selectableSatageID = userData->getSelectableStageID();
    int stageID = _getStageID(currentPage-1+relateivPageID, column);
    
    _setStageText(stageID, stageNode);
    if (stageID < 0 || stageID > STAGE_NUM*WORLD_NUM) {
        
    } else if( stageID < selectableSatageID ) {
        _setUnlocked(stageNode);
    } else if (stageID == selectableSatageID) {
        _setCurrent(stageNode);
    } else {
        _setLocked(stageNode);
    }
}

void SelectScene::_setUnlocked(Node* stageNode) {
    auto lockSprite  = stageNode->getChildByTag(LockSprite);
    auto statusLabel = stageNode->getChildByTag(StatusLabel);
    auto stageButton = stageNode->getChildByTag(StageButton);
    lockSprite->setVisible(false);
    statusLabel->setVisible(true);
    ((LabelTTF*) statusLabel)->setString(_STAGE_STATUS_TEXT[Cleared].c_str());
    ((LabelTTF*) statusLabel)->setFontFillColor(Color3B(255,255,0));
    ((ControlButton*) stageButton)->setHighlighted(false);
    ((ControlButton*) stageButton)->setEnabled(true);
}

void SelectScene::_setLocked(Node* stageNode) {
    auto lockSprite  = stageNode->getChildByTag(LockSprite);
    auto statusLabel = stageNode->getChildByTag(StatusLabel);
    auto stageButton = stageNode->getChildByTag(StageButton);
    auto titleLabel  = stageNode->getChildByTag(TitleLabel);
    lockSprite->setVisible(true);
    statusLabel->setVisible(false);
    ((LabelTTF*)titleLabel)->setString(_DEFAULT_STAGE_NAME.c_str());
    ((LabelTTF*) statusLabel)->setString(_STAGE_STATUS_TEXT[Locked].c_str());
    ((ControlButton*) stageButton)->setHighlighted(false);
    ((ControlButton*) stageButton)->setEnabled(false);
}

void SelectScene::_setCurrent(Node* stageNode) {
    auto lockSprite  = stageNode->getChildByTag(LockSprite);
    auto statusLabel = stageNode->getChildByTag(StatusLabel);
    auto stageButton = stageNode->getChildByTag(StageButton);
    lockSprite->setVisible(false);
    statusLabel->setVisible(true);
    ((LabelTTF*) statusLabel)->setString(_STAGE_STATUS_TEXT[Current].c_str());
    ((LabelTTF*) statusLabel)->setFontFillColor(Color3B(255,0,0));
    ((ControlButton*) stageButton)->setEnabled(true);
    ((ControlButton*) stageButton)->setHighlighted(true);
   
}

void SelectScene::_setStageText(int stageID, Node* stageNode) {
    auto titleLabel  = stageNode->getChildByTag(TitleLabel);
    auto pointLabel  = stageNode->getChildByTag(PointLabel);
    ((LabelTTF*)titleLabel)->setString(_STAGE_NAME[stageID].c_str());
    ((LabelTTF*)pointLabel)->setString((std::to_string(_STAGE_CONSUMPTION_POINT[stageID])).c_str());
}

int SelectScene::_getStageID(int worldNo, int stageNo) {
    if (worldNo < 0) return -1;
    return STAGE_NUM*worldNo+stageNo;
}

int SelectScene::_getWorldNo(int stageID) {
    return stageID / STAGE_NUM;
}
*/


void SelectScene::tappedNextButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedNextButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    //_animationManager->runAnimationsForSequenceNamedTweenDuration("nextPage", 0);
}

void SelectScene::tappedPreviousButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedPreviousButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    if (_currentPageType == SelectRouletteType) {
        auto director = Director::getInstance();
        director->popScene();
    }
    //_animationManager->runAnimationsForSequenceNamedTweenDuration("previousPage", 0);
}

void SelectScene::tappedSelectButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedSelectButton eventType = %d", pControlEventType);
    ControlButton *button = (ControlButton*) pSender;
    int pushedID = button->getParent()->getTag() - NodeTag_SelectScene::ButtonNode;
    
    if (_currentPageType == SelectRouletteType) {
        GameController::getInstance()->setRouletteType((Type::RouletteType)pushedID);
    } else if (_currentPageType == SelectMethod) {
        
    } else if (_currentPageType == SelectMinBet) {
        
    } else if (_currentPageType == SelectZone) {
        
    } else {
        
    }

    
    /*
    _currentPage = ((SelectScene*) this->getParent())->getCurrentPage();
    CCLOG("tappedStageButton eventType = %d", pControlEventType);
    CCLOG("selectedStage is %d-%d", _currentPage, stageNo);
    if (_calcPointConsumption(stageNo)) {
        AudioManager::stopBackGroundMusic();
        AudioManager::playEffect(AudioManager::battleStartEffectFile);
        _selectedStageID = _getStageID(_currentPage, stageNo);
        SelectScene *ssl = (SelectScene*) this->getParent();
        ssl->setSelectedStageID(_selectedStageID);
        ssl->getAnimationManager()->runAnimationsForSequenceNamedTweenDuration("default", 0);
        _setSelectSceneTuchEnable(false);
    }
     */
}

void SelectScene::tappedHatenaButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedHatenaButton eventType = %d", pControlEventType);
    ControlButton *button = (ControlButton*) pSender;
    button->setEnabled(true);
    int stageNo = button->getParent()->getTag() - 100;
    /*
    _currentPage = ((SelectScene*) this->getParent())->getCurrentPage();
    CCLOG("tappedStageButton eventType = %d", pControlEventType);
    CCLOG("selectedStage is %d-%d", _currentPage, stageNo);
    if (_calcPointConsumption(stageNo)) {
        AudioManager::stopBackGroundMusic();
        AudioManager::playEffect(AudioManager::battleStartEffectFile);
        _selectedStageID = _getStageID(_currentPage, stageNo);
        SelectScene *ssl = (SelectScene*) this->getParent();
        ssl->setSelectedStageID(_selectedStageID);
        ssl->getAnimationManager()->runAnimationsForSequenceNamedTweenDuration("default", 0);
        _setSelectSceneTuchEnable(false);
    }
     */
}

void SelectScene::addNumericEditBox() {
    _clearView();
    
    auto firstButtonNode  = this->getChildByTag(NodeTag_SelectScene::ButtonNode);
    auto secondButtonNode = this->getChildByTag(NodeTag_SelectScene::ButtonNode + 1);
    firstButtonNode->setVisible(true);
    secondButtonNode->setVisible(true);
    
    auto firstbutton = (ControlButton*) firstButtonNode->getChildByTag(NodeTag_SelectScene::SelectButton);
    auto secondHatenaButton = (ControlButton*) secondButtonNode->getChildByTag(NodeTag_SelectScene::HatenaButton);
    firstbutton->setVisible(false);
    secondHatenaButton->setVisible(false);
    
    Size size = Size(firstbutton->getContentSize().width, 0.8*firstbutton->getContentSize().height);
    auto editBox = EditBox::create(size, Scale9Sprite::create(Text_EditBox::spriteFileName));
    editBox->setPlaceHolder(Text_EditBox::placeHolder_MinBet);
    editBox->setMaxLength(8);
    editBox->setReturnType(KeyboardReturnType::DONE);
    editBox->setInputMode(EditBox::InputMode::NUMERIC);
    editBox->setDelegate((EditBoxDelegate*)this);
    editBox->setPosition(firstbutton->getPosition());
    editBox->setFontColor(Color3B(0,0,0));
    editBox->setTag(NodeTag_SelectScene::EditBox);
    this->addChild(editBox);
}

void SelectScene::_clearView() {
    for (int i = 0; i < MAX_BUTTON_NUM; i++) {
        auto buttonNode = this->getChildByTag(NodeTag_SelectScene::ButtonNode+i);
        buttonNode->setVisible(false);
    }
}

//
//  SelectScene.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#include "SelectScene.h"
#import "SelectScene.h"
#import "MainMenuLayer.h"
#import "GameLayer.h"
#import "GameComponentLayer.h"
#import "AudioManager.h"
#import "TutorialLayer.h"

USING_NS_CC;

const std::string SelectScene::_DEFAULT_STAGE_NAME = "？？？？？？？？";
const std::array<std::string, WORLD_NUM*STAGE_NUM> SelectScene::_STAGE_NAME = {
    "はじめてのデスク",
    "先輩のデスク",
    "好きな人のデスク",
    "あのデスクは今",
    "司令官のデスク",
    "最高司令官のデスク",
    "総帥のデスク",
    "有名人のデスク",
    "神のデスク",
    "聖戦を生きたデスク",
    "机ってデスク",
    "引き出しの中に・・・！",
    "電脳戦士ポリゴン",
    "ゼーレ、魂の座",
    "ワルプルギスの夜"
};

const std::array<int, WORLD_NUM*STAGE_NUM> SelectScene::_STAGE_CONSUMPTION_POINT = {
    0,5,5,5,8,8,10,12,15,18,20,25,30,35,40
};

const std::array<std::string, SelectScene::StatusNum> SelectScene::_STAGE_STATUS_TEXT = {
    "",
    "Cleared!",
    "New!"
};

SelectScene::SelectScene()
: _animationManager(NULL)
, _currentPage(NULL)
, stagePointLabel(NULL)
, stagePointBarSprite(NULL)
, _selectedStageID(0)
, _SelectSceneNode(NULL)
{
}

SelectScene::~SelectScene()
{
    CC_SAFE_RELEASE_NULL(_animationManager);
    CC_SAFE_RELEASE(stagePointLabel);
    CC_SAFE_RELEASE(stagePointBarSprite);
    CC_SAFE_RELEASE(_SelectSceneNode);
}

void SelectScene::onEnter() {
    Layer::onEnter();
    //AudioManager::playBackGroundMusic(AudioManager::startBgmFile);
}

bool SelectScene::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "stagePointLabel", LabelTTF*, stagePointLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "stagePointBarSprite", Sprite*, stagePointBarSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_SelectSceneNode", Node*, _SelectSceneNode);

    return true;
}

SEL_CallFuncN SelectScene::onResolveCCBCCCallFuncSelector(cocos2d::Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "doneNextPageCallback", SelectScene::doneNextPageCallback);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "donePreviousPageCallback", SelectScene::donePreviousPageCallback);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "finishBattleStartAnim", SelectScene::finishBattleStartAnim);
    return NULL;
}

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
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", SelectScene::tappedBackButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "stageButton1_1", SelectScene::tappedStageButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedYesButton", SelectScene::tappedYesButton);
    return NULL;
}

void SelectScene::doneNextPageCallback(Node* sender) {
    _currentPage++;
    _updateView();
}

void SelectScene::donePreviousPageCallback(Node* sender) {
    _currentPage--;
    _updateView();
}

void SelectScene::finishBattleStartAnim(Node* sender) {
    auto ssl = (SelectScene*)sender;
    int stageID = ssl->getSelectedStageID();
    auto ud = UserData::getInstance();
    if (stageID == 0 /*&& !ud->getIsTutorialDone()*/) {
        ud->setIsTutorialDone(true);
        startTutorialSceneCallback();
    } else {
        startAIGameSceneCallback(stageID);
    }
}

void SelectScene::initScene() {
    // update funcをスケジュールに登録
    this->schedule( schedule_selector(SelectScene::updatePointBar) , 1000.0);
    updatePointBar(0.0);
    auto userData = UserData::getInstance();
    int selectableStageID = userData->getSelectableStageID();
    _currentPage = _getWorldNo(selectableStageID);
    _SelectSceneNode->setVisible(false);
    _updateView();
}

void SelectScene::updatePointBar(float dt)
{
    if(stagePointLabel) _setPointLabel();
    if(stagePointBarSprite) _setPointBarScale();
}

void SelectScene::_updateView(){
    _updatePageView(_currentPage);
    _updateStageView(_currentPage);
}

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

void SelectScene::tappedNextButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedNextButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    _animationManager->runAnimationsForSequenceNamedTweenDuration("nextPage", 0);
}

void SelectScene::tappedPreviousButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedPreviousButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    _animationManager->runAnimationsForSequenceNamedTweenDuration("previousPage", 0);
}

void SelectScene::tappedStageButton(Object* pSender, Control::EventType pControlEventType)
{
    ControlButton *button = (ControlButton*) pSender;
    button->setEnabled(true);
    int stageNo = button->getParent()->getTag() - 100;
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
}

void SelectScene::_setSelectSceneTuchEnable(bool isEnable) {
    auto pageNode  = this->getChildByTag(PageNode + 1);
    for ( int column = 0; column < STAGE_NUM; column++ ) {
        ((ControlButton*)pageNode->getChildByTag(StageNode + column)->getChildByTag(StageButton))->setEnabled(false);
    }
}

void SelectScene::tappedBackButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedBackButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    auto director = Director::getInstance();
    director->popScene();
}

void SelectScene::tappedYesButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedYesButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    this->setVisible(false);
}

void SelectScene::startMainSceneCallback() {
    auto director = Director::getInstance();
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("MainMenuLayer", SelectSceneLoader::loader());
    auto ccbReader = new CCBReader(nodeLoaderLibrary);
    auto node = ccbReader->readNodeGraphFromFile("MainMenu.ccbi");
    auto scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    
    director->pushScene(scene);
}

void SelectScene::startAIGameSceneCallback(int stageID) {
    auto director = Director::getInstance();
    auto scene = GameLayer::createAIScene(stageID);
    GameLayer* gLayer = (GameLayer*) scene->getChildByTag(GameLayer::gameLayerTag);
    gLayer->setSelectedStageID(stageID);
    director->replaceScene(scene);
}

void SelectScene::startTutorialSceneCallback() {
    auto director = Director::getInstance();
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("TutorialLayer", TutorialLayerLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    auto node = ccbReader->readNodeGraphFromFile("Tutorial.ccbi");
    ((TutorialLayer*) node)->initLayer();
    Scene* scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    director->replaceScene(scene);
}

void SelectScene::setAnimationManager(CCBAnimationManager* pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(_animationManager);
    _animationManager = pAnimationManager;
    CC_SAFE_RETAIN(_animationManager);
}

void SelectScene::_setPointLabel() {
    auto ud = UserData::getInstance();
    auto pt = ud->getPointTimer();
    pt->updatePoint();
    int currentPoint = pt->getCurrentPoint();
    int maxPoint = pt->getMaxPoint();
    char str[16];
    sprintf(str, "%d / %d", currentPoint, maxPoint);
    stagePointLabel->setString( str );
}

void SelectScene::_setPointBarScale() {
    auto ud = UserData::getInstance();
    auto pt = ud->getPointTimer();
    stagePointBarSprite->setScaleX( 1.0 * pt->getPercentage() );
}

bool SelectScene::_calcPointConsumption( int column ) {
    auto pageNode  = this->getChildByTag(PageNode+1);
    auto stageNode = pageNode->getChildByTag(StageNode + column);
    auto labelNode = stageNode->getChildByTag(PointLabel);
    String* cns = new String(((LabelTTF*) labelNode)->getString()); // cocos2d::String型 便利過ぎわろた
    auto ud = UserData::getInstance();
    auto pt = ud->getPointTimer();
    if (pt->canPlayGame(cns->intValue())) {
        pt->reducePoint((cns->intValue()));
        return true;
    } else {
        //auto test = this->getParent()->getChildByTag(SelectSceneNode);
        SelectScene *ssl = (SelectScene*) this->getParent();
        ssl->getSelectSceneNode()->setVisible(true);
        return false;
    }
}

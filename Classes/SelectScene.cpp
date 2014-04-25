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
#include "Utility.h"
#include "BetScene.h"

USING_NS_CC;


SelectScene::SelectScene()
: _currentPageType(Type::NonePage)
, _previousPageType(Type::NonePage)
, _nextPageType(Type::NonePage)
{
}

SelectScene::~SelectScene()
{
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
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSelectButton", SelectScene::tappedSelectButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedHatenaButton", SelectScene::tappedHatenaButton);
    return NULL;
}

void SelectScene::initScene() {
    // update funcをスケジュールに登録
    _addNumericEditBox();
    _currentPageType = Type::SelectRouletteTypePage;
    _updateView(_currentPageType);
}

void SelectScene::_updateView(Type::SelectScenePage pageType){
    _clearView();
    
    auto title = (LabelTTF*) this->getChildByTag(NodeTag_SelectScene::Header)->getChildByTag(NodeTag_Header::TiteLabel);
    auto backButton = (LabelTTF*) this->getChildByTag(NodeTag_SelectScene::Header)->getChildByTag(NodeTag_Header::BackButton);
    backButton->cocos2d::Node::setVisible(true);
    auto desc  = (LabelTTF*) this->getChildByTag(NodeTag_SelectScene::TitleLabel);
    
    const char* titleTex;
    const char* descTex;
    const char** buttonTexList;
    int elementNum;
    
    if(pageType == Type::SelectRouletteTypePage) {
        titleTex = Text_SelectScene::title_rouletteType;
        descTex  = Text_SelectScene::desc_rouretteType;
        buttonTexList = Text_List::rouletteType;
        elementNum    = Type::RouletteTypeNum;
        _nextPageType = Type::SelectMinBetPage;
    } else if (pageType == Type::SelectMethodPage) {
        titleTex = Text_SelectScene::title_betMethod;
        descTex  = Text_SelectScene::desc_betMethod;
        buttonTexList = Text_List::method;
        elementNum    = Type::MethodNum;
    } else if (pageType == Type::SelectMinBetPage) {
        titleTex = Text_SelectScene::title_minBet;
        descTex  = Text_SelectScene::desc_minBet;
        buttonTexList = NULL;
        _nextPageType = Type::SelectMethodPage;
        
        _setUpEditBox(Text_EditBox::placeHolder_MinBet);
    } else if (pageType == Type::SelectZonePage) {
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
    _previousPageType = _currentPageType;
    _currentPageType  = pageType;
    
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
                buttonNode->setVisible(true);
                button->setVisible(true);
                hatena->setVisible(true);
            }
        }
    }
}

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
    auto mainScene = (SelectScene*) this->getParent(); // because this node is header.
    if (mainScene->getPreviousPageType() == Type::NonePage) {
        auto director = Director::getInstance();
        director->popScene();
    } else {
        mainScene->_updateView(mainScene->getPreviousPageType());
    }
}

void SelectScene::tappedSelectButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedSelectButton eventType = %d", pControlEventType);
    ControlButton *button = (ControlButton*) pSender;
    int pushedID = button->getParent()->getTag() - NodeTag_SelectScene::ButtonNode;
    
    if (_currentPageType == Type::SelectRouletteTypePage) {
        GameController::getInstance()->setRouletteType((Type::RouletteType)pushedID);
        _updateView(_nextPageType);
    } else if (_currentPageType == Type::SelectMethodPage) {
        float a = GameController::getInstance()->getMinBetCoin();
        CCLOG("test is %f",a);
        
    } else if (_currentPageType == Type::SelectMinBetPage) {
        auto editBox = (EditBox*) this->getChildByTag(NodeTag_SelectScene::EditBox);
        const char* minBet = editBox->getText();
        if (Utility::isDecimalValue(minBet)) {
            GameController::getInstance()->setMinBetCoin(atof(minBet));
            //_updateView(_nextPageType);
            replaceSceneToBetScene();
        } else {
            CCLOG("input value is not decimal.");
        }
    } else if (_currentPageType == Type::SelectZonePage) {
        
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
}

void SelectScene::_addNumericEditBox() {
    auto firstButtonNode  = this->getChildByTag(NodeTag_SelectScene::ButtonNode);
    auto firstbutton = (ControlButton*) firstButtonNode->getChildByTag(NodeTag_SelectScene::SelectButton);
    
    Size size = Size(firstbutton->getContentSize().width, 0.7 * firstbutton->getContentSize().height);
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
    
    _setUpEditBox("");
}

void SelectScene::_clearView() {
    auto editBox = this->getChildByTag(NodeTag_SelectScene::EditBox);
    editBox->setVisible(false);
    
    auto headerNode = this->getChildByTag(NodeTag_SelectScene::Header);
    auto nextButton = headerNode->getChildByTag(NodeTag_Header::NextButton);
    auto backButton = headerNode->getChildByTag(NodeTag_Header::BackButton);
    nextButton->setVisible(false);
    backButton->setVisible(false);
    
    for (int i = 0; i < MAX_BUTTON_NUM; i++) {
        auto buttonNode = this->getChildByTag(NodeTag_SelectScene::ButtonNode+i);
        buttonNode->setVisible(false);
    }
}

void SelectScene::_setUpEditBox(const char* placeHolder) {
    auto editBox = (EditBox*) this->getChildByTag(NodeTag_SelectScene::EditBox);
    if (editBox == NULL) {
        CCLOG("not found editBox node...");
        _addNumericEditBox();
        return;
    }

    editBox->setVisible(true);
    editBox->setPlaceHolder(placeHolder);
    
    auto firstButtonNode  = this->getChildByTag(NodeTag_SelectScene::ButtonNode);
    auto secondButtonNode = this->getChildByTag(NodeTag_SelectScene::ButtonNode + 1);
    firstButtonNode->setVisible(true);
    secondButtonNode->setVisible(true);
    
    auto firstbutton = (ControlButton*) firstButtonNode->getChildByTag(NodeTag_SelectScene::SelectButton);
    auto secondHatenaButton = (ControlButton*) secondButtonNode->getChildByTag(NodeTag_SelectScene::HatenaButton);
    auto secondSelectButton = (ControlButton*) secondButtonNode->getChildByTag(NodeTag_SelectScene::SelectButton);
    auto secondButtonLabel = (LabelTTF*) secondButtonNode->getChildByTag(NodeTag_SelectScene::ButtonLabel);
    firstbutton->setVisible(false);
    secondHatenaButton->setVisible(false);
    secondSelectButton->setVisible(true);
    secondButtonLabel->setString(Text_EditBox::submit);
}

void SelectScene::replaceSceneToBetScene() {
    auto director = Director::getInstance();
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("BetScene", BetSceneLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("BetScene.ccbi");
    ((BetScene*)node)->initScene();
    Scene* scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    director->replaceScene(scene);
}
//
//  BetScene.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#include "BetScene.h"
#include "Utility.h"
#include "Params.h"
#include "NodeTag.h"
#include "AudioManager.h"
#include "GameController.h"
#include "Utility.h"
#include "BetMethodModel.h"

USING_NS_CC;


BetScene::BetScene()
{
}

BetScene::~BetScene()
{
}

SEL_MenuHandler BetScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOGERROR("name_menu_item = %s", pSelectorName);
    
    return NULL;
}

Control::Handler BetScene::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name_control = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedPreviousButton", BetScene::tappedPreviousButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedNextButton", BetScene::tappedNextButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedEditBetButton", BetScene::tappedEditBetButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSettingButton", BetScene::tappedSettingButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedFixedButton", BetScene::tappedFixedButton);
    return NULL;
}

void BetScene::initScene() {
    _updateView();
}

void BetScene::tappedNextButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedNextButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    //_animationManager->runAnimationsForSequenceNamedTweenDuration("nextPage", 0);
}

void BetScene::tappedPreviousButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedPreviousButton eventType = %d", pControlEventType);
    AudioManager::playTapEffect();
    auto mainScene = (BetScene*) this->getParent(); // because this node is header.
        auto director = Director::getInstance();
        director->popScene();
}

void BetScene::tappedEditBetButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedEditBetButton eventType = %d", pControlEventType);
    ControlButton *button = (ControlButton*) pSender;
    int pushedID = button->getParent()->getTag() - NodeTag_BetScene::BetLayerNode;
    
}

void BetScene::tappedSettingButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedSettingButton eventType = %d", pControlEventType);
    ControlButton *button = (ControlButton*) pSender;
    int pushedID = button->getParent()->getTag() - NodeTag_BetScene::BetLayerNode;
    
}

void BetScene::tappedFixedButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedFixedButton eventType = %d", pControlEventType);
    ControlButton *button = (ControlButton*) pSender;
    button->setEnabled(true);
    int stageNo = button->getParent()->getTag() - 100;
}

void BetScene::_updateView() {
    for (int i = 0; i < BET_SLOT_NUM; i++) {
        auto betNode = this->getChildByTag(NodeTag_BetScene::BetLayerNode+i);
        auto methodLabel = (LabelTTF*) betNode->getChildByTag(NodeTag_BetScene::MethodLabel);
        auto zoneLabel = (LabelTTF*) betNode->getChildByTag(NodeTag_BetScene::ZoneLabel);
        auto coinLabel = (LabelTTF*) betNode->getChildByTag(NodeTag_BetScene::CoinLabel);
        auto winrateLabel = (LabelTTF*) betNode->getChildByTag(NodeTag_BetScene::WinRateLabel);
        auto incomeLabel = (LabelTTF*) betNode->getChildByTag(NodeTag_BetScene::IncomeLabel);
        
        BetMethodModel* model = GameController::getInstance()->getMethodModelAt(i);
        methodLabel->setString(model->getBetMethodStr());
        zoneLabel->setString(model->getCurrentBetZoneStr());
        coinLabel->setString(model->getRecomendBetCoinStr());
        winrateLabel->setString(model->getWinRateStr());
        incomeLabel->setString(model->getIncomeStr());
    }
}
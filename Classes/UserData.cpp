//
//  UserData.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2013/11/17.
//
//

#include "UserData.h"
#include "cocos2d.h"

USING_NS_CC;

UserData* UserData::_singleton = NULL;
const std::string UserData::_keySeFlag            = "SE_KEY";
const std::string UserData::_keyBgmFlag           = "BGM_KEY";
const std::string UserData::_keySelectableStageID = "SELECTABLE_STAGE_ID_KEY";
const std::string UserData::_keyRemoteWinNum      = "REMOTE_WIN_KEY";
const std::string UserData::_keyAiWinNum          = "AI_WIN_KEY";
const std::string UserData::_keyMoney             = "MONEY_KEY";

UserData::UserData()
: _isTutorialDone(false)
{
    //_pointTimer = new PointTimer();
    //_userDeck   = new UserDeck();
}

UserData::~UserData()
{
    //delete _pointTimer;
    //delete _userDeck;
}

UserData* UserData::getInstance()
{
    if( NULL == _singleton )
    {
        _singleton = new UserData();
        auto ud = cocos2d::UserDefault::getInstance();
        _singleton->_seFlag            = ud->getBoolForKey(_keySeFlag.c_str(), true);
        _singleton->_bgmFlag           = ud->getBoolForKey(_keyBgmFlag.c_str(), true);
        _singleton->_selectableStageID = ud->getIntegerForKey(_keySelectableStageID.c_str(), 0);
        _singleton->_aiWinNum          = ud->getIntegerForKey(_keyAiWinNum.c_str(), 0);
        _singleton->_remoteWinNum      = ud->getIntegerForKey(_keyRemoteWinNum.c_str(), 0);
    }
    return _singleton;
}

void UserData::switchBgmFlag() {
    _bgmFlag = !_bgmFlag;
}

void UserData::switchSeFlag() {
    _seFlag = !_seFlag;
}

bool UserData::canPlayBgm() {
    return _bgmFlag;
}

bool UserData::canPlaySe() {
    return _seFlag;
}

void UserData::saveSeSetting(){
    auto userDefault = cocos2d::UserDefault::getInstance();
    userDefault->setBoolForKey(_keySeFlag.c_str(), _seFlag);
}

void UserData::saveBgmSetting(){
    auto userDefault = cocos2d::UserDefault::getInstance();
    userDefault->setBoolForKey(_keyBgmFlag.c_str(), _bgmFlag);
}

void UserData::saveSelectableStageID(int stageID){
    auto ud = cocos2d::UserDefault::getInstance();
    ud->setIntegerForKey(_keySelectableStageID.c_str(), _selectableStageID);
}

void UserData::saveAiWinNum(){
    auto ud = cocos2d::UserDefault::getInstance();
    ud->setIntegerForKey(_keyAiWinNum.c_str(), _aiWinNum);
}

void UserData::saveRemoteWinNum(){
    auto ud = cocos2d::UserDefault::getInstance();
    ud->setIntegerForKey(_keyRemoteWinNum.c_str(), _remoteWinNum);
}

void UserData::saveMoney(){
    auto ud = cocos2d::UserDefault::getInstance();
    ud->setIntegerForKey(_keyMoney.c_str(), _money);
}

void UserData::savePoint(){
    //_pointTimer->savePoint();
}

void UserData::saveUserDeck(){
    //_userDeck->saveUserDeck();
}

void UserData::updateSelectableStageID(int stageID) {
    stageID = validateSelectableStageID(stageID);
    setSelectableStageID(stageID);
    saveSelectableStageID(stageID);
}

int UserData::validateSelectableStageID(int stageID ) {
    //int allStageNum = STAGE_NUM * WORLD_NUM - 1;
    //return MAX(MIN(allStageNum, stageID),0);
    return 0;
}



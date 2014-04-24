//
//  UserData.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2013/11/17.
//
//

#ifndef __Casidra__UserData__
#define __Casidra__UserData__

#include <iostream>
#include "cocos2d.h"

class UserData
{
private:
    static const std::string _keySeFlag;
    static const std::string _keyBgmFlag;
    static const std::string _keySelectableStageID;
    static const std::string _keyRemoteWinNum;
    static const std::string _keyAiWinNum;
    static const std::string _keyMoney;
    
private:
    UserData();
    ~UserData();
    static UserData* _singleton;
public:
    static UserData* getInstance();
    
    CC_SYNTHESIZE(bool, _bgmFlag,      BgmFlag);
    CC_SYNTHESIZE(bool, _seFlag,       SeFlag);
    CC_SYNTHESIZE(int,  _selectableStageID, SelectableStageID);
    CC_SYNTHESIZE(int,  _aiWinNum,     AiWinNum);
    CC_SYNTHESIZE(int,  _remoteWinNum, RemoteWinNum);
    CC_SYNTHESIZE(int,  _money,        Money);
    CC_SYNTHESIZE(bool, _isTutorialDone, IsTutorialDone);
    
    bool canPlayBgm();
    bool canPlaySe();
    void switchBgmFlag();
    void switchSeFlag();
    void saveSeSetting();
    void saveBgmSetting();
    void saveSelectableStageID(int stageID);
    void saveAiWinNum();
    void saveRemoteWinNum();
    void saveMoney();
    void savePoint();
    void saveUserDeck();
    void updateSelectableStageID( int stageID );
    int  validateSelectableStageID( int stageID );
};

#endif /* defined(__Casidra__UserData__) */

//
//  BetModel.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/20.
//
//

#ifndef __Casidra__BetMethodModel__
#define __Casidra__BetMethodModel__

#include <iostream>
#include "cocos2d.h"
#include "Params.h"

USING_NS_CC;

class BetMethodModel : public Node {
private:
    bool isWinning(Type::BetZoneType winningBetZone, int number);
    virtual void win();
    virtual void lose();
    
public:
    BetMethodModel();
    virtual ~BetMethodModel();
    virtual bool init();
    CREATE_FUNC(BetMethodModel);
    
    virtual void setUp(Type::BetZoneType betZone);
    virtual void setBetableZoneList();
    virtual float getRecomendBetCoin();
    virtual const char* getBetMethodStr();
    virtual const char* getWinRateStr();
    virtual const char* getCurrentBetZoneStr();
    virtual const char* getRecomendBetCoinStr();
    virtual const char* getIncomeStr();
    virtual const char** getBetableBetZoneStr();
    virtual int getBetableBetZoneNum();
    void updateData(int number);
    
    CC_SYNTHESIZE_READONLY(Type::BetZoneType, _currentBetZone, CurrentBetZone);
    CC_SYNTHESIZE_READONLY(int, _startGameCount, StartGameCount);
    CC_SYNTHESIZE_READONLY(Type::MethodType, _methodType, MethodType);
    CC_SYNTHESIZE(float, _currentBetCoin, CurrentBetCoin);
    CC_SYNTHESIZE_READONLY(float, _income, Income);
    CC_SYNTHESIZE_READONLY(int, _winCount, WinCount);
    CC_SYNTHESIZE_READONLY(bool, _isInitialized, IsInitialized);
    CC_SYNTHESIZE_READONLY(std::vector<float>, _betCoinList, BetCoinList);
    CC_SYNTHESIZE_READONLY(Type::BetZoneCategory, _betZoneCategory, BetZoneCategory);
    
    float getCurrentWinRate();
};

#endif /* defined(__Casidra__BetModel__) */

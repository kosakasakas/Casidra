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
    bool isWinning(Type::BetZone winningBetZone, int number);
    virtual void win();
    virtual void lose();
    
public:
    BetMethodModel();
    virtual ~BetMethodModel();
    virtual bool init();
    CREATE_FUNC(BetMethodModel);
    
    virtual void setUp(Type::BetZone betZone);
    virtual std::vector<Type::BetZone> getBetableZone();
    virtual float getRecomendBetCoin();
    void updateData(int number);
    
    CC_SYNTHESIZE_READONLY(Type::BetZone, _currentBetZone, CurrentBetZone);
    CC_SYNTHESIZE_READONLY(int, _startGameCount, StartGameCount);
    CC_SYNTHESIZE_READONLY(float, _currentBetCoin, CurrentBetCoin);
    CC_SYNTHESIZE_READONLY(float, _oldBetCoin, OldBetCoin);
    CC_SYNTHESIZE_READONLY(int, _winCount, WinCount);
    CC_SYNTHESIZE_READONLY(bool, _isInialized, IsInitialized);
    
    float getCurrentWinRate();
};

#endif /* defined(__Casidra__BetModel__) */

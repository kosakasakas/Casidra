//
//  GameController.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2013/11/17.
//
//

#ifndef __Casidra__GameController__
#define __Casidra__GameController__

#include <iostream>
#include "cocos2d.h"
#include "Params.h"
#include "BetMethodModel.h"

#define BET_SLOT_NUM 3

class GameController
{
private:
    GameController();
    virtual ~GameController();
    static GameController* _singleton;
    void _incrementGameCount();
    void _addResult(int number);
    bool _isValidSlot(int slotNo);
    
public:
    static GameController* getInstance();
    
    CC_SYNTHESIZE(Type::RouletteType, _rouletteType, RouletteType);
    CC_SYNTHESIZE(int, _globalGameCount, GlobalGameCount);
    CC_SYNTHESIZE(float, _minBetCoint, MinBetCoin);
    CC_SYNTHESIZE(float, _currentAsset, CurrentAsset);
    CC_SYNTHESIZE_READONLY(std::vector<int>, _resultList, ResultList);
    CC_SYNTHESIZE_READONLY(bool, _isCurrentGameEnded, IsCurrentGameEnded);
    CC_SYNTHESIZE_READONLY(std::vector<BetMethodModel*>, _betMethodModelSlot, BetMEthodModelSlot);
    
    void resetAll();
    void resetGame();
    int getResultAt(int gamecount);
    void startGame();
    void endGame(int resultNumber);
    void setNewMethodModel(int slopNo, Type::Method method);
};

#endif /* defined(__Casidra__GameController__) */

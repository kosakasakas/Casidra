//
//  BetModel.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/20.
//
//

#ifndef __Casidra__MonteCalroModel__
#define __Casidra__MonteCalroModel__

#include <iostream>
#include "cocos2d.h"
#include "Params.h"
#include "BetMethodModel.h"

USING_NS_CC;

class MonteCalroModel : public BetMethodModel {
private:
    
public:
    MonteCalroModel();
    virtual ~MonteCalroModel();
    virtual bool init();
    static MonteCalroModel* create();
    
    const char* getBetMethodStr();
    std::vector<Type::BetZoneType> getBetableZone();
    float getRecomendBetCoin();
};

#endif /* defined(__Casidra__BetModel__) */

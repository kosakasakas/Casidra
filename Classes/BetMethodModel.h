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
#include "RouletteConfig.h"

class BetMethodModel {
// var
private:
    
public:
    
// func
private:
    
public:
    BetMethodModel();
    virtual ~BetMethodModel();
    virtual std::vector<int> getBetableZone();
    virtual BetZone getRecomendZone();
};

#endif /* defined(__Casidra__BetModel__) */

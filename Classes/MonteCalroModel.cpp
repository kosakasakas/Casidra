//
//  MonteCalroModel.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/20.
//
//

#include "MonteCalroModel.h"
#include "GameController.h"
#include "Utility.h"

MonteCalroModel::MonteCalroModel()
{
}

MonteCalroModel::~MonteCalroModel()
{
}

bool MonteCalroModel::init() {
    if (!Node::init()) {
        return false;
    }
    
    _currentBetCoin = GameController::getInstance()->getMinBetCoin();
    return true;
}

std::vector<Type::BetZone> MonteCalroModel::getBetableZone() {
    std::vector<Type::BetZone> vec;
    return vec;
}

float MonteCalroModel::getRecomendBetCoin() {
    if (!_isInialized) {
        CCLOG("please initialize method model.");
        return 0.0;
    }
    
    return GameController::getInstance()->getMinBetCoin();
}
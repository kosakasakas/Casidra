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
    if (!BetMethodModel::init()) {
        return false;
    }
    _currentBetZone = Type::Red;
    _isInitialized = true;
    return true;
}

MonteCalroModel* MonteCalroModel::create()
{
    auto p = new MonteCalroModel();
    if(p && p->init()){
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

std::vector<Type::BetZoneType> MonteCalroModel::getBetableZone() {
    std::vector<Type::BetZoneType> vec;
    vec.push_back(Type::Red);
    vec.push_back(Type::Black);
    vec.push_back(Type::Hight);
    vec.push_back(Type::Low);
    vec.push_back(Type::Odd);
    vec.push_back(Type::Even);
    return vec;
}

float MonteCalroModel::getRecomendBetCoin() {
    
    return GameController::getInstance()->getMinBetCoin();
}

const char* MonteCalroModel::getBetMethodStr() {
    return Text_List::method[Type::MonteCarlo];
}
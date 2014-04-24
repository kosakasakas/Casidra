//
//  BetMethodModel.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/20.
//
//

#include "BetMethodModel.h"
#include "GameController.h"

BetMethodModel::BetMethodModel()
: _isInialized(false)
, _startGameCount(0)
, _currentBetCoin(0.0)
, _oldBetCoin(0.0)
, _winCount(0)
, _currentBetZone(Type::NoZone)
{
}

BetMethodModel::~BetMethodModel()
{
}

bool BetMethodModel::init() {
    if (!Node::init()) {
        return false;
    }
    
    _currentBetCoin = GameController::getInstance()->getMinBetCoin();
    return true;
}

void BetMethodModel::setUp(Type::BetZone betZone) {
    _currentBetZone = betZone;
    _currentBetCoin = GameController::getInstance()->getMinBetCoin();
    _oldBetCoin = 0.0;
    _isInialized = true;
}

float BetMethodModel::getCurrentWinRate() {
    int gameCount = GameController::getInstance()->getGlobalGameCount() - _startGameCount;
    return (gameCount == 0) ? 0.0 : (float) _winCount / (float) gameCount;
}

std::vector<Type::BetZone> BetMethodModel::getBetableZone() {
    std::vector<Type::BetZone> vec;
    return vec;
}

float BetMethodModel::getRecomendBetCoin() {
    if (!_isInialized) {
        CCLOG("please initialize method model.");
        return 0;
    }
    
    return GameController::getInstance()->getMinBetCoin();
}

void BetMethodModel::updateData(int number) {
    if (!_isInialized) {
        CCLOG("please initialize method model.");
        return;
    }
    
    if (isWinning(_currentBetZone, number)) {
        win();
    } else {
        lose();
    }
}

bool BetMethodModel::isWinning(Type::BetZone betZone, int number) {
    int* checkList;
    int num;
    if (betZone == Type::Red) {
        num = 16;
        int array[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,17,30,32,34,36};
        checkList = array;
    } else if (betZone == Type::Black) {
        num = 16;
        int array[] = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
        checkList = array;
    } else {
        num = 0;
        int array[] = {};
        checkList = array;
    }
    
    for (int i = 0; i < num; i++) {
        if (checkList[i] == number) {
            return true;
        }
    }
    return false;
}

void BetMethodModel::win() {
    
}

void BetMethodModel::lose() {
    
}

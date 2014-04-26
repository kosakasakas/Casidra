//
//  BetMethodModel.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/20.
//
//

#include "BetMethodModel.h"
#include "GameController.h"
#include "Utility.h"

BetMethodModel::BetMethodModel()
: _currentBetZone(Type::NoZone)
, _startGameCount(0)
, _currentBetCoin(0)
, _previousBetCoin(0)
, _income(0.0)
, _winCount(0)
, _isInitialized(false)
, _methodType(Type::NoneMethod)
{
}

BetMethodModel::~BetMethodModel()
{
}

bool BetMethodModel::init() {
    if (!Node::init()) {
        return false;
    }
    return true;
}

void BetMethodModel::setUp(Type::BetZoneType betZone) {
    _currentBetZone = betZone;
    _currentBetCoin = GameController::getInstance()->getMinBetCoin();
    _previousBetCoin = 0.0;
    _isInitialized = true;
}

float BetMethodModel::getCurrentWinRate() {
    int gameCount = GameController::getInstance()->getGlobalGameCount() - _startGameCount;
    return (gameCount == 0) ? 0.0 : (float) _winCount / (float) gameCount;
}

std::vector<Type::BetZoneType> BetMethodModel::getBetableZone() {
    std::vector<Type::BetZoneType> vec;
    return vec;
}

float BetMethodModel::getRecomendBetCoin() {
    return 0.0; // you have to overrride this method.
}

void BetMethodModel::updateData(int number) {
    if (!_isInitialized) {
        CCLOG("please initialize method model.");
        return;
    }
    
    if (isWinning(_currentBetZone, number)) {
        win();
    } else {
        lose();
    }
    _currentBetCoin = getRecomendBetCoin();
}

bool BetMethodModel::isWinning(Type::BetZoneType betZone, int number) {
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
    ++_winCount;
}

void BetMethodModel::lose() {
    
}

const char* BetMethodModel::getBetMethodStr() {
    return Text_Config::notInitialized;
}
const char* BetMethodModel::getWinRateStr() {
    return  Utility::getStrFromFloatValue(getCurrentWinRate());
}
const char* BetMethodModel::getCurrentBetZoneStr() {
    return Text_List::zone[_currentBetZone];
}
const char* BetMethodModel::getIncomeStr() {
    return Utility::getStrFromFloatValue(_income);
}
const char* BetMethodModel::getRecomendBetCoinStr() {
    return Utility::getStrFromFloatValue(_currentBetCoin);
}
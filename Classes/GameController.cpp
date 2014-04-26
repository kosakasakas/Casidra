//
//  GameController.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2013/11/17.
//
//

#include "GameController.h"
#include "BetMethodModelFactory.h"

USING_NS_CC;

GameController* GameController::_singleton = NULL;

GameController::GameController()
: _rouletteType(Type::American)
, _minBetCoint(1.0)
, _isCurrentGameEnded(false)
, _globalGameCount(0)
, _currentAsset(0.0)
{
    // 一個目はデフォルトモンテカルロ
    /*BetMethodModel* model = BetMethodModelFactory::createBetMethodModel(Type::MonteCarlo);
    model->retain();
    _betMethodModelSlot.push_back(model);*/
    
    // 残りは未設定
    for (int i = 0; i < BET_SLOT_NUM; i++) {
        BetMethodModel* model = new BetMethodModel();
        model->retain();
        _betMethodModelSlot.push_back(model);
    }
}

GameController::~GameController()
{
    std::vector<BetMethodModel*>::iterator it;
    for(it=_betMethodModelSlot.begin(); it!=_betMethodModelSlot.end(); ++it){
        CC_SAFE_RELEASE(*it);
    }
}

GameController* GameController::getInstance()
{
    if( NULL == _singleton )
    {
        _singleton = new GameController();
    }
    
    return _singleton;
}

void GameController::_incrementGameCount() {
    ++_globalGameCount;
}

void GameController::_addResult(int number) {
    _resultNumberList.push_back(number);
    _isCurrentGameEnded = true;
}

void GameController::resetAll() {
    _currentAsset = 0;
    resetGame();
}

void GameController::resetGame() {
    _globalGameCount = 0;
    _resultNumberList.clear();
}

int GameController::getResultAt(int gamePoint) {
    if (_globalGameCount < gamePoint || gamePoint < 0 ) {
        return 0;
    }
    
    return _resultNumberList.at(gamePoint);
}

void GameController::endGame(int resultNumber) {
    _addResult(resultNumber);
    _isCurrentGameEnded = true;
}

void GameController::startGame() {
    _incrementGameCount();
    _isCurrentGameEnded = false;
}

void GameController::setNewMethodModel(int slotNo, Type::MethodType method) {
    if (!_isValidSlot(slotNo)) {
        return;
    }
    
    BetMethodModel* oldModel = _betMethodModelSlot.at(slotNo);
    oldModel->release();
    BetMethodModel* newModel = BetMethodModelFactory::createBetMethodModel(method);
    newModel->retain();
    _betMethodModelSlot.insert(_betMethodModelSlot.begin()+slotNo, newModel);
}

bool GameController::_isValidSlot(int slotNo) {
    if (0 > slotNo && slotNo < BET_SLOT_NUM) {
        return true;
    }
    return false;
}

BetMethodModel* GameController::getMethodModelAt(int slotID) {
    return _betMethodModelSlot.at(slotID);
}

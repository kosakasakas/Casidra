//
//  BetMethodModelFactory.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/24.
//
//

#include "BetMethodModelFactory.h"
#include "MonteCalroModel.h"

BetMethodModel* BetMethodModelFactory::createBetMethodModel(Type::MethodType method) {
    BetMethodModel* model;
    if (method == Type::MonteCarlo) {
        model = MonteCalroModel::create();
    } else {
        model = BetMethodModel::create();
    }
    return model;
}
//
//  BetMethodModelFactory.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/24.
//
//

#include "BetMethodModelFactory.h"

BetMethodModel* BetMethodModelFactory::createBetMethodModel(Type::Method method) {
    BetMethodModel* model;
    if (method == Type::MonteCarlo) {
        model = BetMethodModel::create();
    } else {
        model = BetMethodModel::create();
    }
    return model;
}
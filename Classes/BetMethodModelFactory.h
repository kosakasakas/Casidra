//
//  BetMethodModelFactory.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/24.
//
//

#ifndef __Casidra__BetMethodModelFactory__
#define __Casidra__BetMethodModelFactory__

#include <iostream>
#include "Params.h"
#include "BetMethodModel.h"

class BetMethodModelFactory {
public:
    static BetMethodModel* createBetMethodModel(Type::MethodType method);
};

#endif /* defined(__Casidra__BetMethodModelFactory__) */

//
//  Utility.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/23.
//
//

#ifndef __Casidra__Utility__
#define __Casidra__Utility__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Utility
{
private:
public:
    static bool isDecimalValue(const char* text);
    static const char* getStrFromFloatValue(float val);
};

#endif /* defined(__Casidra__Utility__) */

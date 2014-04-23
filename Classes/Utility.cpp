//
//  Utility.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/23.
//
//

#include "Utility.h"

Scene* Utility::getCurrentScene(){
    auto director = Director::getInstance();
    return director->getRunningScene();
}
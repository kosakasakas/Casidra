//
//  AppMacros.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/14.
//
//

#ifndef Casidra_AppMacros_h
#define Casidra_AppMacros_h

#include "cocos2d.h"

typedef struct tagResource {
    cocos2d::Size size;  // 論理解像度
    char directory[100]; // 優先検索するリソースディレクトリ
    float scaleFactor;   // コンテンツのスケール倍率
} Resource;

static Resource iphone   = {cocos2d::Size(320, 480), "resources-iphone",   1.0};
static Resource iphone4s = {cocos2d::Size(320, 480), "resources-iphonehd", 2.0};
static Resource iphone5  = {cocos2d::Size(320, 568), "resources-iphonehd", 2.0};

#endif

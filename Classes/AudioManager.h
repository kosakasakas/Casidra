//
//  AudioManager.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/02/08.
//
//

#ifndef __Casidra__AudioManager__
#define __Casidra__AudioManager__

#include <iostream>

class AudioManager
{
public:
    static const std::string startBgmFile;
    static const std::string battleBgmFile;
    static const std::string battleStartEffectFile;
    static const std::string battleWinBgmFile;
    static const std::string battleLoseBgmFile;
    static const std::string mainBgmFile;
    static const std::string tapEffectFile;
    static const std::string buildUpFile;

private:
public:
    static void playBackGroundMusic(std::string file);
    static void stopBackGroundMusic();
    static void playEffect(std::string file);
    static void playTapEffect();
    static void preloadBattleEffect();
};

#endif /* defined(__Deskwar__AudioManager__) */

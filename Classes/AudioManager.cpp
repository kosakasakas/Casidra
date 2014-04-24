//
//  AudioManager.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/02/08.
//
//

#include "AudioManager.h"
#include "SimpleAudioEngine.h"
#include "UserData.h"

const std::string AudioManager::startBgmFile  = "opening.m4a";
const std::string AudioManager::battleBgmFile = "battle.m4a";
const std::string AudioManager::mainBgmFile = "fight-demo.m4a";
const std::string AudioManager::battleWinBgmFile = "battleWin.m4a";
const std::string AudioManager::battleLoseBgmFile = "battleLose.m4a";
const std::string AudioManager::battleStartEffectFile = "battleStart.caf";
//const std::string AudioManager::mainBgmFile   = "mainBgm.m4a";
const std::string AudioManager::tapEffectFile = "tap.caf";
const std::string AudioManager::buildUpFile = "buildUp.caf";

void AudioManager::playBackGroundMusic(std::string file) {
    auto audioEngin = CocosDenshion::SimpleAudioEngine::getInstance();
    auto userDate = UserData::getInstance();
    if (userDate->canPlayBgm()) {
        audioEngin->playBackgroundMusic(file.c_str(), true);
    }
}

void AudioManager::stopBackGroundMusic() {
    auto audioEngin = CocosDenshion::SimpleAudioEngine::getInstance();
    audioEngin->stopBackgroundMusic();
}

void AudioManager::playEffect(std::string file) {
    auto audioEngin = CocosDenshion::SimpleAudioEngine::getInstance();
    auto userDate = UserData::getInstance();
    if (userDate->canPlayBgm()) {
        audioEngin->playEffect(file.c_str());
    }
}

void AudioManager::playTapEffect() {
    playEffect(tapEffectFile);
}
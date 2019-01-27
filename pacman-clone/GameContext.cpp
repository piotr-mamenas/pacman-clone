#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "GameContext.h"

const std::string GAME_NAME = "";
const unsigned int SCREEN_FPS = 60;
const unsigned int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

GameContext::GameContext(int screenWidth, int screenHeight, bool isWindowMode) 
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->isWindowMode = isWindowMode;
}

bool GameContext::init() 
{
    bool success = true;

    return success;
}
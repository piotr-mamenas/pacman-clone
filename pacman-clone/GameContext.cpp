#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "GameContext.h"
#include "SDL2Memory.h"

const char* GAME_NAME = "";
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

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else 
    {
        SDL_WindowFlags windowFlag;
        if (this->isWindowMode)
        {
            windowFlag = SDL_WINDOW_SHOWN;
        }
        else 
        {
            windowFlag = SDL_WINDOW_FULLSCREEN;
        }
        _gameWindow = SDL2Memory::WindowSharedPtr(SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, windowFlag));
    }

    return success;
}

void GameContext::close()
{
}
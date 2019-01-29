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
        if (isWindowMode)
        {
            windowFlag = SDL_WINDOW_SHOWN;
        }
        else 
        {
            windowFlag = SDL_WINDOW_FULLSCREEN;
        }
        gameWindow = SDL2Memory::WindowSharedPtr(SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, windowFlag));
        gameRenderer = SDL2Memory::RendererSharedPtr(SDL_CreateRenderer(gameWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        
        if (gameRenderer == NULL)
        {
            std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError();
            success = false;
        }
    }

    return success;
}

void GameContext::close()
{
}

void GameContext::_refreshScene()
{
    _clearScreen();

}

void GameContext::_clearScreen()
{
    SDL_SetRenderDrawColor(gameRenderer.get(), 0, 0, 0, 250);
    SDL_SetRenderTarget(gameRenderer.get(), 0);
    SDL_RenderClear(gameRenderer.get());
}
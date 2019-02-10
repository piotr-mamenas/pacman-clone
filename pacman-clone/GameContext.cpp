#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "GameContext.h"
#include "GameTimer.h"
#include "Pacman.h"
#include "SDL2Memory.h"

const char* GAME_NAME = "";
const unsigned int SCREEN_FPS = 60;
const unsigned int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

GameContext::GameContext(int screenWidth, int screenHeight, bool isWindowMode) 
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    _isWindowMode = isWindowMode;
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
        if (_isWindowMode)
        {
            windowFlag = SDL_WINDOW_SHOWN;
        }
        else 
        {
            windowFlag = SDL_WINDOW_FULLSCREEN;
        }
        _gameWindow = SDL2Memory::WindowSharedPtr(SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, windowFlag));
        _gameRenderer = SDL2Memory::RendererSharedPtr(SDL_CreateRenderer(_gameWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

        if (_gameRenderer == NULL)
        {
            std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError();
            success = false;
        }

        _gameAssetManager = std::make_shared<GameAssetManager>(_gameRenderer);

        SDL_Event e;
        bool quit = false;

        GameTimer fpsTimer;
        GameTimer capTimer;
        int countedFrames = 0;
        fpsTimer.start();

        while (!quit)
        {
            capTimer.start();
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                //_currentPlayer->handleInteraction(e, units);
            }

            _refreshScene();

            int frameTicks = capTimer.getTicks();
            if (frameTicks < SCREEN_TICKS_PER_FRAME)
            {
                // Capped at 20 atm, but VSync is active so can be turned off if necessary
                SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
            }
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
    
    auto pacman = std::make_shared<Pacman>(0, 0, _gameAssetManager.get());
    pacman->render(_gameAssetManager.get(), _gameRenderer);

    SDL_RenderPresent(_gameRenderer.get());
}

void GameContext::_clearScreen()
{
    SDL_SetRenderDrawColor(_gameRenderer.get(), 0, 0, 0, 0);
    SDL_SetRenderTarget(_gameRenderer.get(), 0);
    SDL_RenderClear(_gameRenderer.get());
}
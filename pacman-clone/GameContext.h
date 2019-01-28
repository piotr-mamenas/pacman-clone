#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "SDL2Memory.h"

class GameContext
{
protected:
    SDL2Memory::WindowSharedPtr _gameWindow;

    int screenWidth;
    int screenHeight;
    bool isWindowMode;
public:
    GameContext(int screenWidth, int screenHeight, bool isWindowMode);
    bool init();
    void close();
};

#endif
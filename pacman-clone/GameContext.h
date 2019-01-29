#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "SDL2Memory.h"

class GameContext
{
private:
    void _refreshScene();
    void _clearScreen();
protected:
    SDL2Memory::WindowSharedPtr gameWindow;
    SDL2Memory::RendererSharedPtr gameRenderer;

    int screenWidth;
    int screenHeight;
    bool isWindowMode;
public:
    GameContext(int screenWidth, int screenHeight, bool isWindowMode);
    bool init();
    void close();
};

#endif
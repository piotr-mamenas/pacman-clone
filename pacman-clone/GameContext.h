#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <memory>
#include <vector>

#include "GameAssetManager.h"
#include "Pacman.h"
#include "Ghost.h"
#include "SDL2Memory.h"

class GameContext
{
private:
    SDL2Memory::WindowSharedPtr _gameWindow;
    SDL2Memory::RendererSharedPtr _gameRenderer;
    std::shared_ptr<GameAssetManager> _gameAssetManager;
    std::shared_ptr<Pacman> _pacman;
    std::vector<Ghost> _ghosts;

    int _screenWidth;
    int _screenHeight;
    bool _isWindowMode;

    void _refreshScene();
    void _clearScreen();
public:
    GameContext(int screenWidth, int screenHeight, bool isWindowMode);
    bool init();
    void resetGame();
    void close();
};

#endif
#ifndef GAMEASSETMANAGER_H
#define GAMEASSETMANAGER_H

#include <string>
#include "SDL2Memory.h"

class GameAssetManager
{
private:
    SDL2Memory::RendererSharedPtr _renderer;

    SDL2Memory::TextureSharedPtr _loadTexture(std::string path);
};

#endif
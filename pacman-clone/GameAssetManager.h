#ifndef GAMEASSETMANAGER_H
#define GAMEASSETMANAGER_H

#include <string>
#include <map>

#include "SDL2Memory.h"

class GameAssetManager
{
private:
    SDL2Memory::RendererSharedPtr _renderer;
    std::map<int, SDL2Memory::TextureSharedPtr> _textures;

    SDL2Memory::TextureSharedPtr _loadTexture(std::string path);
    std::map<int, SDL2Memory::TextureSharedPtr> _loadGameResources();
public:
    GameAssetManager(SDL2Memory::RendererSharedPtr gameRenderer);
};

#endif
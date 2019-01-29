#ifndef GAMEASSETMANAGER_H
#define GAMEASSETMANAGER_H

#include <string>
#include <map>

#include <SDL2/SDL.h>

#include "SDL2Memory.h"

class GameAssetManager
{
private:
    SDL2Memory::RendererSharedPtr _renderer;
    std::map<int, SDL_Texture*> _textures;

    SDL_Texture* _loadTexture(std::string path);
    std::map<int, SDL_Texture*> _loadGameTextures();
public:
    GameAssetManager(SDL2Memory::RendererSharedPtr gameRenderer);
    SDL_Texture* getTexture(int id);
};

#endif
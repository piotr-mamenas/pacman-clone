#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "GameAssetManager.h"
#include "SDL2Memory.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

GameAssetManager::GameAssetManager(SDL2Memory::RendererSharedPtr gameRenderer)
{
    _renderer = gameRenderer;
    _loadGameResources();
}

std::map<int, SDL2Memory::TextureSharedPtr> GameAssetManager::_loadGameResources()
{
    int spriteId;
    std::string path;
    std::map<int, SDL2Memory::TextureSharedPtr> textureMap;

    try
    {
        std::ifstream spriteFile("sprites.json");
        json sprites;
        spriteFile >> sprites;

        for (auto& sprite : sprites.at("sprites"))
        {
            spriteId = sprite.at("id").get<int>();
            path = sprite.at("spriteSheetImage").get<std::string>();
            
            SDL2Memory::TextureSharedPtr texture = SDL2Memory::TextureSharedPtr(_loadTexture(path));
            textureMap.insert(std::pair<int, SDL2Memory::TextureSharedPtr>(spriteId, texture));
        }
        return textureMap;
    }
    catch (json::parse_error& e)
    {
        std::cout << "message: " << e.what() << '\n'
            << "exception id: " << e.id << '\n'
            << "byte position of error: " << e.byte << std::endl;

        return textureMap;
    }
}

SDL2Memory::TextureSharedPtr GameAssetManager::_loadTexture(std::string path)
{
    SDL2Memory::TextureSharedPtr loadedTexture;

    SDL2Memory::SurfaceSharedPtr loadedSurface = SDL2Memory::SurfaceSharedPtr(IMG_Load(path.c_str()));
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface.get(), SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0));
        loadedTexture = SDL2Memory::TextureSharedPtr(SDL_CreateTextureFromSurface(_renderer.get(), loadedSurface.get()));
        if (loadedTexture == NULL)
        {
            printf("Unable to create texture %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
    }
    return loadedTexture;
}
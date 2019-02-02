#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "GameAssetManager.h"
#include "SDL2Memory.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

GameAssetManager::GameAssetManager(SDL2Memory::RendererSharedPtr gameRenderer)
{
    _renderer = gameRenderer;
    _textures = _loadGameTextures();
}

SDL_Texture* GameAssetManager::getTexture(int id)
{
    std::map<int, SDL_Texture*>::iterator textureIterator = _textures.find(id);
    if (textureIterator != _textures.end())
    {
        return textureIterator->second;
    }
    throw std::runtime_error("Could not find texture id: " + id);
}

std::map<int, SDL_Texture*> GameAssetManager::_loadGameTextures()
{
    int spriteId;
    std::string path;
    std::map<int, SDL_Texture*> textureMap;

    try
    {
        std::ifstream spriteFile("sprites.json");
        json sprites;
        spriteFile >> sprites;

        for (auto& sprite : sprites.at("sprites"))
        {
            spriteId = sprite.at("id").get<int>();
            path = sprite.at("image").get<std::string>();
            
            SDL_Texture* texture = _loadTexture(path);
            textureMap.insert(std::pair<int, SDL_Texture*>(spriteId, texture));
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

SDL_Texture* GameAssetManager::_loadTexture(std::string path)
{
    SDL_Texture* loadedTexture = nullptr;

    SDL2Memory::SurfaceSharedPtr loadedSurface = SDL2Memory::SurfaceSharedPtr(IMG_Load(path.c_str()));
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface.get(), SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0));
        loadedTexture = SDL_CreateTextureFromSurface(_renderer.get(), loadedSurface.get());
        if (loadedTexture == NULL)
        {
            auto errorMessage = ("Unable to create texture " + path ) + "! SDL Error: " + SDL_GetError();
            throw std::runtime_error(errorMessage);
        }
    }
    return loadedTexture;
}
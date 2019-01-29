#include <string>

#include "GameAssetManager.h"
#include "SDL2Memory.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
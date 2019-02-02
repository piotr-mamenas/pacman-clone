#include "GameObject.h"
#include "GameAssetManager.h"

#include <SDL2/SDL.h>
#include "SDL2Memory.h"

GameObject::GameObject(int posX, int posY, int width, int height, int spriteId, GameAssetManager* assetManager) 
{
    this->width = width;
    this->height = height;
    this->spriteId = spriteId;

    SDL_Texture* texture = assetManager->getTexture(spriteId);
    int clipCounter = 0;
    int spriteSheetWidth = 0;
    int spriteSheetHeight = 0;
    SDL_QueryTexture(texture, NULL, NULL, &spriteSheetWidth, &spriteSheetHeight);

    if (spriteSheetWidth % this->width != 0)
    {
        throw std::invalid_argument("Loaded SpriteSheet Width is not divisable by Sprite Width");
    }

    if (spriteSheetHeight % this->height != 0)
    {
        throw std::invalid_argument("Loaded SpriteSheet Height is not divisable by Sprite Height");
    }

    for (int cntY = 0; cntY < (spriteSheetHeight / this->height); cntY++)
    {
        for (int cntX = 0; cntX < (spriteSheetWidth / this->width); cntX++)
        {
            clipCounter++;

            SDL_Rect spriteClip;
            spriteClip.w = this->width;
            spriteClip.h = this->height;
            spriteClip.x = cntX * this->width;
            spriteClip.y = cntY * this->height;

            _clips.insert(std::pair<int, SDL_Rect>(clipCounter, spriteClip));
        }
    }
}

SDL_Rect GameObject::_getClip(int clipId)
{
    std::map<int, SDL_Rect>::iterator clipIterator = _clips.find(clipId);
    if (clipIterator != _clips.end())
    {
        return clipIterator->second;
    }
    throw std::runtime_error("Could not find clip id: " + clipId);
}

SDL_Rect GameObject::_getClipByCurrentState()
{
    int clipId;
    std::map<int, int>::iterator mappingIteractor = stateClipMapping.find(_stateId);
    if (mappingIteractor != stateClipMapping.end())
    {
        clipId = mappingIteractor->second;
    }
    return _getClip(clipId);
}

void GameObject::render(GameAssetManager* gameAssetManager, SDL2Memory::RendererSharedPtr renderer)
{
    SDL_Rect currentClip = _getClipByCurrentState();
    SDL_Rect currentPosition;
    currentPosition.x = posX;
    currentPosition.y = posY;
    currentPosition.w = currentClip.w;
    currentPosition.h = currentClip.h;

    SDL_RenderCopy(renderer.get(), gameAssetManager->getTexture(spriteId), &currentClip, &currentPosition);
}
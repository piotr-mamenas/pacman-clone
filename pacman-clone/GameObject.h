#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>

#include <SDL2/SDL.h>

#include "GameAssetManager.h"
#include "SDL2Memory.h"

class GameObject
{
private:
    int _stateId;
    std::map<int, SDL_Rect> _clips;

    SDL_Rect _getClip(int clipId);
    SDL_Rect _getClipByCurrentState();
protected:
    int posX;
    int posY;
    int width;
    int height;
    int spriteId;
    std::map<int, int> stateClipMapping;

public:
    GameObject(int posX, int posY, int width, int height, int spriteId, GameAssetManager* assetManager);
    void render(GameAssetManager* gameAssetManager, SDL2Memory::RendererSharedPtr renderer);
};

#endif
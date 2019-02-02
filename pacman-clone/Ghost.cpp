#include <string>

#include "Ghost.h"
#include "GameObject.h"
#include "GameAssetManager.h"

Ghost::Ghost(int posX, int posY, int width, int height, int spriteId, std::string colorRgb, GameAssetManager* assetManager)
    : GameObject(posX, posY, width, height, spriteId, assetManager)
{
    _colorRgb = colorRgb;
}
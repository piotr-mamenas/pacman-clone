#include <string>

#include "Ghost.h"
#include "GameObject.h"
#include "GameAssetManager.h"

Ghost::Ghost(int posX, int posY, std::string colorRgb, GameAssetManager* assetManager)
    : GameObject(posX, posY, 16, 16, 2, assetManager)
{
    stateClipMapping.insert(std::pair<int, int>(1, 1));
    _colorRgb = colorRgb;
}
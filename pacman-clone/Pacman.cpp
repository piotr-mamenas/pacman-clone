#include "Pacman.h"

#include "GameObject.h"
#include "GameAssetManager.h"

Pacman::Pacman(int posX, int posY, GameAssetManager* assetManager)
    : GameObject(posX, posY, 16, 16, 1, assetManager)
{
    stateClipMapping.insert(std::pair<int, int>(1, 1));
}
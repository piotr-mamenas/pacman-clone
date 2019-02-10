#ifndef PACMAN_H
#define PACMAN_H

#include "GameObject.h"

class Pacman : public GameObject
{
public:
    Pacman(int posX, int posY, GameAssetManager* assetManager);
};

#endif
#ifndef GHOST_H
#define GHOST_H

#include <string>
#include "GameObject.h"

class Ghost : public GameObject
{
private:
    std::string _colorRgb;
public: 
    Ghost(int posX, int posY, int width, int height, int spriteId, std::string colorRgb, GameAssetManager* assetManager);
};

#endif
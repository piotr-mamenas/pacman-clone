#ifndef GHOST_H
#define GHOST_H

#include <string>
#include "GameObject.h"

class Ghost : public GameObject
{
private:
    std::string _colorRgb;
public: 
    Ghost(int posX, int posY, std::string colorRgb, GameAssetManager* assetManager);
};

#endif
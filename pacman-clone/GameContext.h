#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

class GameContext
{
protected:
    int screenWidth;
    int screenHeight;
    bool isWindowMode;
public:
    GameContext(int screenWidth, int screenHeight, bool isWindowMode);
    bool init();
};

#endif
#include "Main.h"
#include "GameContext.h"

int main(int argc, char* argv[])
{
    bool isWindowMode = true;
    std::shared_ptr<GameContext> context = std::make_shared<GameContext>(640, 480, isWindowMode);

    bool isGameInitialized = context->init();
    if (!isGameInitialized)
    {
        printf("Failed to initialize Game Engine!\n");
    }
    context->close();
    return 0;
}
#include <memory>
#include <stdexcept>

#include "GameContext.h"

#ifdef main
#undef main
#endif 

int main(int argc, char* argv[])
{
    bool isWindowMode = true;
    std::shared_ptr<GameContext> context = std::make_shared<GameContext>(640,480,isWindowMode);

    bool isGameInitialized = context->init();
    if (!isGameInitialized)
    {
        throw std::runtime_error("Failed to initialize Game Engine!\n");
    }
    context->close();
    return 0;
}
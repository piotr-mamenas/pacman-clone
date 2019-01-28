#ifndef SDLADAPTER_H
#define SDLADAPTER_H

#include <memory>
#include <stdint.h>

#include <SDL2/SDL.h>

struct SDL_Deleter {
    void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
    void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
    void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
    void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
};

template<class T, class D = std::default_delete<T>>
struct shared_ptr_with_deleter : public std::shared_ptr<T>
{
    explicit shared_ptr_with_deleter(T* t = nullptr)
        : std::shared_ptr<T>(t, D()) {};

    void reset(T* t = nullptr)
    {
        std::shared_ptr<T>::reset(t, D());
    }
};

namespace SDL2Memory
{
    using SurfaceSharedPtr = shared_ptr_with_deleter<SDL_Surface, SDL_Deleter>;
    using TextureSharedPtr = shared_ptr_with_deleter<SDL_Texture, SDL_Deleter>;
    using RendererSharedPtr = shared_ptr_with_deleter<SDL_Renderer, SDL_Deleter>;
    using WindowSharedPtr = shared_ptr_with_deleter<SDL_Window, SDL_Deleter>;
}

#endif
//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_WINDOW_HPP
#define TD3D_WINDOW_HPP

#include <GL/glu.h>
#include <GL/gl.h>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "Dimension.hpp"
#include <string>

class Window
{
public:
    Window(const Dimension& size, const std::string& title)
            : m_window(
            SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.width, size.height,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    {
        if (m_window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    ~Window()
    {
        SDL_DestroyWindow(m_window);
    }

    void swap()
    {
        SDL_GL_SwapWindow(m_window);
    }

    SDL_Window* getWindowHandle() const
    {
        return m_window;
    }

private:
    SDL_Window* m_window;
};

#endif //TD3D_WINDOW_HPP

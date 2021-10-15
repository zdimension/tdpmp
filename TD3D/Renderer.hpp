//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_RENDERER_HPP
#define TD3D_RENDERER_HPP

#include <GL/glu.h>
#include <GL/gl.h>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "Window.hpp"
#include "primitives/Dimension.hpp"
#include <string>
#include <functional>

class Renderer
{
public:
    explicit Renderer(const Dimension& size)
            : m_window(size, "SDL GL Application"), m_glContext(SDL_GL_CreateContext(m_window.getWindowHandle()))
    {
        if (m_glContext == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70, size.getAspectRatio(), 1, 1000);

        glEnable(GL_DEPTH_TEST);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    ~Renderer()
    {
        SDL_GL_DeleteContext(m_glContext);
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void swap()
    {
        m_window.swap();
    }

    void runLoop(const std::function<void(Uint32)>& loop)
    {
        m_window.runLoop(
                [this, loop](Uint32 elapsed)
                {
                    clear();
                    loop(elapsed);
                    swap();
                });
    }

    const Window& getSdlWindow() const
    {
        return m_window;
    }

private:
    Window m_window;
    SDL_GLContext m_glContext;
};

#endif //TD3D_RENDERER_HPP

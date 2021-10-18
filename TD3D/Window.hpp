//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_WINDOW_HPP
#define TD3D_WINDOW_HPP

#include <GL/glu.h>
#include <GL/gl.h>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "primitives/Dimension.hpp"
#include <string>
#include <functional>
#include <utility>

class Window
{
public:
    Window(const Dimension& size, std::string title)
            : m_title(std::move(title)), m_window(
            SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.width, size.height,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)), m_inputStatus({})
    {
        if (m_window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        m_inputStatus.keys = SDL_GetKeyboardState(nullptr);
    }

    ~Window()
    {
        SDL_DestroyWindow(m_window);
    }

    void swap()
    {
        SDL_GL_SwapWindow(m_window);
    }

    SDL_Window* getRawWindowHandle() const
    {
        return m_window;
    }

    void runLoop(const std::function<void(Uint32)>& loop)
    {
        SDL_Event event;

        Uint32 last_time = SDL_GetTicks();
        Uint32 current_time, elapsed_time;
        Uint32 start_time;

        for (;;)
        {
            start_time = SDL_GetTicks();

            m_inputStatus.buttons = SDL_GetMouseState(&m_inputStatus.mx, &m_inputStatus.my);
            m_inputStatus.scrolled = false;

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_MOUSEWHEEL:
                        m_inputStatus.scrolled = true;
                        m_inputStatus.dx = event.wheel.x;
                        m_inputStatus.dy = event.wheel.y;
                        break;
                    case SDL_QUIT:
                        return;
                }
            }

            current_time = SDL_GetTicks();
            elapsed_time = current_time - last_time;
            last_time = current_time;

            loop(elapsed_time);

            elapsed_time = SDL_GetTicks() - start_time;
            if (elapsed_time < 10)
            {
                SDL_Delay(10 - elapsed_time);
            }
        }
    }

    const auto& getInputStatus() const
    {
        return m_inputStatus;
    }

private:
    std::string m_title;
    SDL_Window* m_window;
    struct
    {
        const Uint8* keys;
        Uint32 buttons;
        int mx, my;
        bool scrolled;
        int dx, dy;
    } m_inputStatus;
};

#endif //TD3D_WINDOW_HPP

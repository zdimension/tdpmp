//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_APPLICATION_HPP
#define TD3D_APPLICATION_HPP

#include "Dimension.hpp"
#include "Renderer.hpp"

class Application
{
public:
    Application()
            : m_renderer(Dimension(800, 600))
    {
    }

    void run();

private:
    Renderer m_renderer;
};

#endif //TD3D_APPLICATION_HPP

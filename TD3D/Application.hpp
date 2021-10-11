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
            : m_renderer(Dimension(640, 480))
    {
    }

    void run();

    void drawCube(double angleX, double angleZ);

private:
    Renderer m_renderer;
};

#endif //TD3D_APPLICATION_HPP

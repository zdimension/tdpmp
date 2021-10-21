//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_APPLICATION_HPP
#define TD3D_APPLICATION_HPP

#include "primitives/Dimension.hpp"
#include "Renderer.hpp"
#include "scenes/BaseScene.hpp"

class Application
{
public:
    Application();

    void run();

private:
    Renderer m_renderer;
    std::unique_ptr<BaseScene> m_scene;
};

#endif //TD3D_APPLICATION_HPP

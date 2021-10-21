//
// Created by Tom on 21/10/2021.
//

#ifndef TD3D_AXES_HPP
#define TD3D_AXES_HPP

#include "Scene.hpp"

class Axes : public Scene<Cube>
{
public:
    Axes()
    {
        // trièdre
        add({{0.2, 0.2, 0.2},
                  {0,   0,   0},
                  {0,   0,   0},
                  {{255, 255, 0}}});
        add({{1,   0.1, 0.1},
                  {0.5, 0,   0},
                  {0,   0,   0},
                  {{255, 0, 0}}});
        add({{0.1, 1,   0.1},
                  {0,   0.5, 0},
                  {0,   0,   0},
                  {{0, 255, 0}}});
        add({{0.1, 0.1, 1},
                  {0,   0,   0.5},
                  {0,   0,   0},
                  {{0, 0, 255}}});
    }
};

#endif //TD3D_AXES_HPP

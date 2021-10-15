//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_CUBE_HPP
#define TD3D_CUBE_HPP


#include <GL/gl.h>
#include <GL/glu.h>
#include "../primitives/Vector3d.hpp"
#include "../primitives/Color.hpp"
#include "Entity.hpp"
#include <optional>
#include <SDL2/SDL.h>

struct Cube : public Entity
{
    constexpr Cube(const Vector3d& size, const Vector3d& position, const Vector3d& angle,
                   const std::optional<Color>& color = {})
            : size(size), position(position), angle(angle), color(color)
    {
    }

    void draw() const override;

    void update(Uint32 elapsed) override
    {
    };

    Vector3d size;
    Vector3d position;
    Vector3d angle;
    std::optional<Color> color;
};


#endif //TD3D_CUBE_HPP

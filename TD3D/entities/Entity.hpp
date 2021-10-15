//
// Created by Tom on 13/10/2021.
//

#ifndef TD3D_ENTITY_HPP
#define TD3D_ENTITY_HPP

#include <SDL2/SDL.h>

class Entity
{
public:
    virtual void draw() const = 0;

    virtual void update(Uint32 elapsed) = 0;
};


#endif //TD3D_ENTITY_HPP

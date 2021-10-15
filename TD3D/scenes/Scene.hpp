//
// Created by Tom on 13/10/2021.
//

#ifndef TD3D_SCENE_H
#define TD3D_SCENE_H


#include <vector>
#include <memory>
#include "../shapes/Cube.hpp"

class Scene : public Entity
{
public:
    Scene() : objects()
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

    void add(Cube&& object)
    {
        objects.push_back(std::make_shared<Cube>(object));
    }

    template<typename T>
    void add(T&& object)
    {
        objects.push_back(std::make_shared<T>(object));
    }

public:
    virtual void draw() const override
    {
        for (auto& object: objects)
        {
            object->draw();
        }
    }

    virtual void update(Uint32 elapsed) override
    {
        for (auto& object: objects)
        {
            object->update(elapsed);
        }
    }

protected:
    std::vector<std::shared_ptr<Cube>> objects;
};


#endif //TD3D_SCENE_H

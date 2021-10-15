//
// Created by Tom on 13/10/2021.
//

#ifndef TD3D_SCENE_H
#define TD3D_SCENE_H


#include <vector>
#include <memory>
#include "../entities/Cube.hpp"

class Scene : public Entity
{
public:
    Scene();

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
    void draw() const override
    {
        for (auto& object: objects)
        {
            object->draw();
        }
    }

    void update(Uint32 elapsed) override
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

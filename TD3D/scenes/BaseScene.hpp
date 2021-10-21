//
// Created by Tom on 21/10/2021.
//

#ifndef TD3D_BASESCENE_HPP
#define TD3D_BASESCENE_HPP

#include "../entities/Entity.hpp"
#include <memory>
#include <vector>

class BaseScene : public Entity
{
public:
    BaseScene();

    void add(std::unique_ptr<Entity>& object)
    {
        objects.push_back(std::move(object));
    }

    template<typename T>
    void add(T&& object)
    {
        objects.push_back(std::make_unique<T>(object));
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
    std::vector<std::shared_ptr<Entity>> objects;
};

#include <vector>
#include <memory>
#include "../entities/Cube.hpp"

#endif //TD3D_BASESCENE_HPP

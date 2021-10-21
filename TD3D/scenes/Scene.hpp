//
// Created by Tom on 13/10/2021.
//

#ifndef TD3D_SCENE_H
#define TD3D_SCENE_H


#include <vector>
#include <memory>
#include "../entities/Cube.hpp"
#include "BaseScene.hpp"

template<typename T>
class Scene : public BaseScene
{
public:
    Scene() : BaseScene()
    {

    }

    std::shared_ptr<T> add(T&& object)
    {
        auto sh_ptr = std::make_shared<T>(object);
        objects.push_back(sh_ptr);
        spec_objects.push_back(sh_ptr);
        return sh_ptr;
    }

protected:
    std::vector<std::shared_ptr<T>> spec_objects;
};


#endif //TD3D_SCENE_H

//
// Created by Tom on 13/10/2021.
//

#ifndef TD3D_ORBITS_HPP
#define TD3D_ORBITS_HPP

#include "../entities/Cube.hpp"
#include "Scene.hpp"
#include <array>

constexpr double G = 6.67408e-11;

struct PhysicalCube : public Cube
{
    PhysicalCube(const Vector3d& size, const Vector3d& position, const Vector3d& angle,
                 const Color& color, double mass) : Cube(size, position, angle, {color}), mass(mass)
    {
    }

    void draw() const override
    {
        glBegin(GL_LINE_STRIP);
        size_t i = trail_length;
        size_t p = trail_pos;
        for (; i > 0; i--)
        {
            if (p-- == 0)
            {
                p = trail.size() - 1;
            }
            const Vector3d& v = trail[p];
            glColor4ub(color->r, color->g, color->b, (GLubyte) (255.0l * i / trail_length));
            glVertex3d(v.x, v.y, v.z);
        }
        glEnd();

        Cube::draw();
    }

    void update(Uint32 elapsed) override
    {
        velocity += accel * (elapsed / 1000.0);
        position += velocity * (elapsed / 1000.0);

        if ((trail_last_ticks += elapsed) > 10)
        {
            trail_last_ticks = 0;

            trail[trail_pos] = position;

            if (++trail_pos == trail.size())
            {
                trail_pos = 0;
            }

            if (trail_length < trail.size())
            {
                trail_length++;
            }
        }
    };

    void addForce(const Vector3d& force)
    {
        accel += force / mass;
    }

    Vector3d accel = {0, 0, 0};
    Vector3d velocity = {0, 0, 0};
    double mass;

private:
    std::array<Vector3d, 1600> trail;
    Uint32 trail_last_ticks = 0;
    size_t trail_pos = 0;
    size_t trail_length = 0;
};


class Orbits : public Scene
{
public:
    Orbits() : Scene(), phy_objects{}
    {
        add({{2, 2, 2}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, 9.0e12})
                ->velocity += {0, 0, 0};
        add({{0.7, 0.7, 0.7}, {20, 0, 0}, {0, 0, 0}, {192, 192, 192}, 7.6e10})
                ->velocity += {0, -3, -3};
        add({{0.7, 0.7, 0.7}, {3, 0, 20}, {0, 0, 0}, {255, 192, 120}, 7.6e10})
                ->velocity += {0, -3, -3};
        add({{0.7, 0.7, 0.7}, {-8, -3, -6}, {0, 0, 0}, {138, 5, 130}, 7.6e10})
                ->velocity += {0, -3, -3};
    }

    std::shared_ptr<PhysicalCube> add(PhysicalCube&& object)
    {
        auto sh_ptr = std::make_shared<PhysicalCube>(object);
        objects.push_back(sh_ptr);
        phy_objects.push_back(sh_ptr);
        return sh_ptr;
    }

    void update(Uint32 elapsed) override
    {
        for (auto& obj: phy_objects)
        {
            obj->accel = {0, 0, 0};
        }

        for (auto i = phy_objects.begin(); i != phy_objects.end(); ++i)
        {
            for (auto j = i; ++j != phy_objects.end();)
            {
                auto delta = (*j)->position - (*i)->position;
                double force = G * (*i)->mass * (*j)->mass / delta.normSquared();
                auto nd = delta.normalize();
                (*i)->addForce(nd * force);
                (*j)->addForce(nd * -force);
            }
        }

        Scene::update(elapsed);
    }

private:
    std::vector<std::shared_ptr<PhysicalCube>> phy_objects;
};


#endif //TD3D_ORBITS_HPP

//
// Created by Tom on 11/10/2021.
//

#include "Application.hpp"
#include <vector>
#include <iostream>
#include "Cube.hpp"
#include <ranges>
#include <memory>

struct RotatingCube : public Cube
{
    void update(Uint32 elapsed) override
    {
        Cube::update(elapsed);

        angle.x += rotSpeed * elapsed;
        angle.z += rotSpeed * elapsed;
    }

    double rotSpeed;

    RotatingCube(const Vector3d& size, const Vector3d& position, const Vector3d& angle,
                 const std::optional<Color>& color, double rotSpeed) : Cube(size, position, angle, color),
                                                                       rotSpeed(rotSpeed)
    {
    }
};

void Application::run()
{
    std::vector<std::unique_ptr<Cube>> cubes;
    // axes
    cubes.push_back(std::make_unique<Cube>(Cube{{0.2, 0.2, 0.2},
                                                {0,   0,   0},
                                                {0,   0,   0},
                                                {{255, 255, 0}}}));
    cubes.push_back(std::make_unique<Cube>(Cube{{1,   0.1, 0.1},
                                                {0.5, 0,   0},
                                                {0,   0,   0},
                                                {{255, 0, 0}}}));
    cubes.push_back(std::make_unique<Cube>(Cube{{0.1, 1,   0.1},
                                                {0,   0.5, 0},
                                                {0,   0,   0},
                                                {{0, 255, 0}}}));
    cubes.push_back(std::make_unique<Cube>(Cube{{0.1, 0.1, 1},
                                                {0,   0,   0.5},
                                                {0,   0,   0},
                                                {{0, 0, 255}}}));


    double speed = 0.05;
    for (int i = 1; i < 10; speed = -speed, i++)
    {
        cubes.push_back(std::make_unique<RotatingCube>(
                RotatingCube{{i / 10.0, i / 10.0, i / 10.0},
                             {2.0 * (i - 5.0), 0, 0},
                             {0, 0, 0}, {}, speed}));
    }

    Vector3d camera(3, 3, 3);


    const auto& mouse = m_renderer.getSdlWindow().getInputStatus();
    const Uint8* keystate = mouse.keys;
    struct { bool moving; int x, y; } oldmouse;

    m_renderer.runLoop(
            [&cubes, &camera, &keystate, &mouse, &oldmouse](Uint32 elapsed_time)
            {
                const double delta_angle = elapsed_time / 1000.0;

                if (keystate[SDL_SCANCODE_LEFT])
                    camera = camera.rotate(-delta_angle, Axis::Y);
                else if (keystate[SDL_SCANCODE_RIGHT])
                    camera = camera.rotate(delta_angle, Axis::Y);

                if (keystate[SDL_SCANCODE_UP])
                    camera = camera.rotate(delta_angle, Axis::LAT);
                else if (keystate[SDL_SCANCODE_DOWN])
                    camera = camera.rotate(-delta_angle, Axis::LAT);

                if (mouse.scrolled)
                    camera = camera * (mouse.dy > 0 ? 0.9 : (1 / 0.9));

                if (mouse.buttons & SDL_BUTTON_LMASK)
                {
                    if (oldmouse.moving)
                    {
                        camera = camera.rotate((mouse.mx - oldmouse.x) * -delta_angle, Axis::Y);
                        camera = camera.rotate((mouse.my - oldmouse.y) * delta_angle, Axis::LAT);
                    }

                    oldmouse = {true, mouse.mx, mouse.my};
                }
                else
                    oldmouse.moving = false;

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                gluLookAt(camera.x, camera.y, camera.z, 0, 0, 0, 0, 1, 0);

                for (auto& cube: cubes)
                {
                    cube->update(elapsed_time);
                    cube->draw();
                }
            });
}


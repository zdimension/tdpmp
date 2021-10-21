//
// Created by Tom on 11/10/2021.
//

#include <iostream>
#include "Application.hpp"
#include "scenes/Orbits.hpp"
#include "scenes/Axes.hpp"
#include "scenes/Voxels.hpp"

void Application::run()
{
    struct
    {
        double lat, lon, norm;
        double px, pz;
    } camera = {20, 45, 5, 0, 0};

    const auto& mouse = m_renderer.getSdlWindow().getInputStatus();
    const Uint8* keystate = mouse.keys;
    struct
    {
        bool moving;
        int x, y;
    } oldmouse{}, oldpan{};
    auto& scene = this->m_scene;

    m_renderer.runLoop(
            [&camera, &keystate, &mouse, &oldmouse, &scene, &oldpan](Uint32 elapsed_time)
            {
                const double rotate_speed = elapsed_time / 50.0;

                if (keystate[SDL_SCANCODE_UP])
                    camera.lat += rotate_speed;
                else if (keystate[SDL_SCANCODE_DOWN])
                    camera.lat -= rotate_speed;

                if (camera.lat > 360)
                    camera.lat -= 360;
                else if (camera.lat < 0)
                    camera.lat += 360;

                const double lon_speed = (camera.lat > 90 && camera.lat <= 270) ? -rotate_speed : rotate_speed;

                if (keystate[SDL_SCANCODE_LEFT])
                    camera.lon -= lon_speed;
                else if (keystate[SDL_SCANCODE_RIGHT])
                    camera.lon += lon_speed;

                if (mouse.scrolled)
                    camera.norm *= (mouse.dy > 0 ? 0.9 : (1 / 0.9));

                if (mouse.buttons & SDL_BUTTON_LMASK)
                {
                    if (oldmouse.moving)
                    {
                        camera.lon += (mouse.mx - oldmouse.x) * lon_speed;
                        camera.lat += (mouse.my - oldmouse.y) * rotate_speed;
                    }

                    oldmouse = {true, mouse.mx, mouse.my};
                }
                else
                    oldmouse.moving = false;


                if (mouse.buttons & SDL_BUTTON_RMASK)
                {
                    if (oldpan.moving)
                    {
                        const double pan_speed = camera.norm * elapsed_time / 4000.0;
                        camera.px += (mouse.mx - oldpan.x) * pan_speed;
                        camera.pz += (mouse.my - oldpan.y) * pan_speed;
                    }

                    oldpan = {true, mouse.mx, mouse.my};
                }
                else
                    oldpan.moving = false;

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                glTranslated(0, 0, -camera.norm);

                // arcball rotation
                glRotated(camera.lat, 1, 0, 0);
                glRotated(camera.lon, 0, 1, 0);

                // panning
                auto pan_rot = Vector3d(camera.px, 0, camera.pz).rotate(rad(-camera.lon), Axis::Y);
                glTranslated(pan_rot.x, 0, pan_rot.z);

                scene->update(elapsed_time);
                scene->draw();
            });
}

Application::Application()
        : m_renderer(Dimension(1600, 900)), m_scene(std::make_unique<Voxels>())
{
    m_scene->add(Axes{});
}


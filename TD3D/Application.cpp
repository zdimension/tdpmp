//
// Created by Tom on 11/10/2021.
//

#include "Application.hpp"

void Application::run()
{
    SDL_Event event;

    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time, elapsed_time;
    Uint32 start_time;

    double angleX = 0, angleZ = 0;

    for (;;)
    {
        start_time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_WINDOWEVENT:
                    if (m_event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        m_camera->resizeWindow(windowWidth, windowHeight);
                        glViewport(0, 0, windowWidth, windowHeight);

                        logFileStderr("MESSAGE:Resizing window...\n");
                        resizeWindow(m_event.window.data1, m_event.window.data2);
                    }
                    break;
                case SDL_QUIT:
                    exit(0);
            }
        }

        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;
        last_time = current_time;

        angleZ += 0.05 * elapsed_time;
        angleX += 0.05 * elapsed_time;

        drawCube(angleX, angleZ);

        elapsed_time = SDL_GetTicks() - start_time;
        if (elapsed_time < 10)
        {
            SDL_Delay(10 - elapsed_time);
        }
    }
}

void Application::drawCube(double angleX, double angleZ)
{
    m_renderer.clear();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(3, 4, 2, 0, 0, 0, 0, 0, 1);

    glRotated(angleZ, 0, 0, 1);
    glRotated(angleX, 1, 0, 0);

    glBegin(GL_QUADS);

    glColor3ub(255, 0, 0); //face rouge
    glVertex3d(1, 1, 1);
    glVertex3d(1, 1, -1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, 1, 1);

    glColor3ub(0, 255, 0); //face verte
    glVertex3d(1, -1, 1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, 1, -1);
    glVertex3d(1, 1, 1);

    glColor3ub(0, 0, 255); //face bleue
    glVertex3d(-1, -1, 1);
    glVertex3d(-1, -1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, -1, 1);

    glColor3ub(255, 255, 0); //face jaune
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, -1, 1);

    glColor3ub(0, 255, 255); //face cyan
    glVertex3d(1, 1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, 1, -1);

    glColor3ub(255, 0, 255); //face magenta
    glVertex3d(1, -1, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, -1, 1);

    glEnd();

    glFlush();
    m_renderer.swap();
}

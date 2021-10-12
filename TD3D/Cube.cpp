//
// Created by Tom on 11/10/2021.
//

#include "Cube.hpp"

void Cube::draw() const
{
    glPushMatrix();

    glTranslated(position.x, position.y, position.z);

    glRotated(angle.x, 1, 0, 0);
    glRotated(angle.y, 0, 1, 0);
    glRotated(angle.z, 0, 0, 1);
    glScaled(size.x / 2, size.y / 2, size.z / 2);

    glBegin(GL_QUADS);

    if (color)
        glColor3ub(color->r, color->g, color->b);

    if (!color)
        glColor3ub(255, 0, 0); //face rouge
    glVertex3d(1, 1, 1);
    glVertex3d(1, 1, -1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, 1, 1);

    if (!color)
        glColor3ub(0, 255, 0); //face verte
    glVertex3d(1, -1, 1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, 1, -1);
    glVertex3d(1, 1, 1);

    if (!color)
        glColor3ub(0, 0, 255); //face bleue
    glVertex3d(-1, -1, 1);
    glVertex3d(-1, -1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, -1, 1);

    if (!color)
        glColor3ub(255, 255, 0); //face jaune
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, -1, 1);

    if (!color)
        glColor3ub(0, 255, 255); //face cyan
    glVertex3d(1, 1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, 1, -1);

    if (!color)
        glColor3ub(255, 0, 255); //face magenta
    glVertex3d(1, -1, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, -1, 1);

    glEnd();
    glFlush();

    glPopMatrix();
}

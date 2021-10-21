//
// Created by Tom on 13/10/2021.
//

#ifndef TD3D_ROTATINGCUBES_HPP
#define TD3D_ROTATINGCUBES_HPP

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


class RotatingCubes : public Scene<RotatingCube>
{
public:
    RotatingCubes() : Scene()
    {
        double speed = 0.05;
        for (int i = 1; i < 10; speed = -speed, i++)
        {
            add(
                    RotatingCube{{i / 10.0, i / 10.0, i / 10.0},
                                 {2.0 * (i - 5.0), 0, 0},
                                 {0, 0, 0}, {}, speed});
        }
    }
};


#endif //TD3D_ROTATINGCUBES_HPP

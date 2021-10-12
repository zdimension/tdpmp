//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_VECTOR3D_HPP
#define TD3D_VECTOR3D_HPP

#include <cmath>
#include <ostream>

enum class Axis
{
    X,
    Y,
    Z,
    LAT
};

struct Vector3d
{
    constexpr Vector3d(double x, double y, double z)
            : x(x), y(y), z(z)
    {
    }

    [[nodiscard]] Vector3d rotate(double theta, Axis axis) const
    {
        double c = cos(theta);
        double s = sin(theta);

        switch (axis)
        {
            case Axis::X:
                return {x, y * c - z * s, y * s + z * c};
            case Axis::Y:
                return {x * c + z * s, y, -x * s + z * c};
            case Axis::Z:
                return {x * c - y * s, x * s + y * c, z};
            case Axis::LAT:
                double norm = sqrt(x * x + y * y + z * z);
                double lat = asin(y / norm) + theta;
                double lon = atan2(z, x);
                return Vector3d{cos(lat) * cos(lon), sin(lat), cos(lat) * sin(lon)} * norm;
        }

        throw std::invalid_argument("Invalid axis");
    }

    Vector3d operator*(double factor) const
    {
        return {x * factor, y * factor, z * factor};
    }

    double x;
    double y;
    double z;

    friend std::ostream& operator<<(std::ostream& os, const Vector3d& d)
    {
        os << "{ " << d.x << ", " << d.y << ", " << d.z << " }";
        return os;
    }
};

#endif //TD3D_VECTOR3D_HPP

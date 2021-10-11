//
// Created by Tom on 11/10/2021.
//

#ifndef TD3D_DIMENSION_HPP
#define TD3D_DIMENSION_HPP


struct Dimension
{
    int width = 0;
    int height = 0;

    constexpr Dimension() = default;

    constexpr Dimension(int width, int height) : width(width), height(height)
    {
    }

    inline double getAspectRatio() const
    {
        return (double) width / height;
    }
};


#endif //TD3D_DIMENSION_HPP

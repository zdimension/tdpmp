//
// Created by Tom on 12/10/2021.
//

#ifndef TD3D_COLOR_HPP
#define TD3D_COLOR_HPP


union Color
{
    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    uint32_t rgb;
};


#endif //TD3D_COLOR_HPP

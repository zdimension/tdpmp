//
// Created by Tom on 26/10/2021.
//

#ifndef TDIMG_IMAGE_H
#define TDIMG_IMAGE_H

#include <cstdint>
#include <fstream>
#include <ostream>
#include <memory>
#include <cassert>
#include <limits>
#include <valarray>
#include <cmath>

struct Pixel
{
    uint8_t r, g, b;

    constexpr bool operator==(const Pixel& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    /**
     * @return the complementary color in sRGB space
     */
    [[nodiscard]] constexpr Pixel negate() const
    {
        return {static_cast<uint8_t>(~r), static_cast<uint8_t>(~g), static_cast<uint8_t>(~b)};
    }

    /**
     * Linearizes a gamma-corrected sRGB component (factor 2.2)
     * @param ic component
     */
    static double inverse_gamma(uint8_t ic)
    {
        double c = ic / 255.0;
        if (c <= 0.04045)
            return c / 12.92;
        else
            return std::pow(((c + 0.055) / (1.055)), 2.4);
    }

    static constexpr double rY = 0.212655;
    static constexpr double gY = 0.715158;
    static constexpr double bY = 0.072187;

    /**
     * @return perceived brightness of the color on [0; 255]
     */
    [[nodiscard]] uint8_t brightness() const
    {
        double v = rY * inverse_gamma(r) +
                   gY * inverse_gamma(g) +
                   bY * inverse_gamma(b);
        if (v <= 0.0031308)
            v *= 12.92;
        else
            v = 1.055 * std::pow(v, 1.0 / 2.4) - 0.055;
        return (uint8_t) lround(v * 255 + 0.5);
    }
};

std::ifstream& operator>>(std::ifstream& in, Pixel& rgb);

std::ostream& operator<<(std::ostream& out, const Pixel& rgb);

class Image
{
public:
    /**
     * Substitutes a color for another
     */
    void replace_color(const Pixel&& orig, const Pixel&& subst);

    /**
     * Negates the image
     */
    void negate();

    /**
     * Converts the image to black-and-white depending on the perceived brightness of each pixel
     * @param brightness brightness threshold
     */
    void threshold(uint8_t brightness);

    /**
     * Computes the symmetry of the image around the SO-NE axis (antidiagonal)
     */
    void symmetry();

    Image() : width(0), height(0)
    {

    }

    [[maybe_unused]] explicit Image(const std::string& filename) : Image()
    {
        read(filename);
    }

    void read(const std::string& filename);

    void write(const std::string& filename) const;

private:
    friend std::ifstream& operator>>(std::ifstream& in, Image& img);

    friend std::ostream& operator<<(std::ostream& out, const Image& img);

    [[nodiscard]] constexpr size_t pix_count() const
    {
        return width * height;
    }

    size_t width, height;
    std::unique_ptr<Pixel[]> buffer;
};


#endif //TDIMG_IMAGE_H

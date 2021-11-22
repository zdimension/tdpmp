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
#include <utility>

struct Color
{
    union
    {
        struct
        {
            uint8_t r, g, b;
        };
        uint32_t rgb;
    };

    constexpr bool operator==(const Color& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    bool operator<(const Color& other) const
    {
        return rgb < other.rgb;
    }

    /**
     * @return the complementary color in sRGB space
     */
    [[nodiscard]] constexpr Color negate() const
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

std::ifstream& operator>>(std::ifstream& in, Color& rgb);

std::ostream& operator<<(std::ostream& out, const Color& rgb);

typedef size_t palette_id;
typedef std::vector<palette_id> buffer_t;
typedef std::vector<Color> palette_t;

class Image
{
public:
    /**
     * Substitutes a color for another
     */
    void replace_color(const Color&& orig, const Color&& subst);

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

    Image(Image&& other) noexcept: width(other.width), height(other.height), buffer(std::move(other.buffer)),
                                   palette(std::move(other.palette))
    {
    }

    Image& operator=(Image&& other) noexcept
    {
        width = other.width;
        height = other.height;
        buffer = std::move(other.buffer);
        palette = std::move(other.palette);
        return *this;
    }

    Color operator()(size_t x, size_t y) const
    {
        assert(x < width && y < height);
        return palette[buffer[y * width + x]];
    }

    palette_id& operator()(size_t x, size_t y)
    {
        assert(x < width && y < height);
        return buffer[y * width + x];
    }

    void read(const std::string& filename);

    void write(const std::string& filename) const;

    class Iterator
    {
        using iterator_category = std::contiguous_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Color;
        using pointer = const value_type*;
        using reference = const value_type&;

    public:
        reference operator*() const
        {
            return m_palette[*m_ptr];
        }

        pointer operator->()
        {
            return &m_palette[*m_ptr];
        }

        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b)
        {
            return a.m_ptr == b.m_ptr;
        };

        friend bool operator!=(const Iterator& a, const Iterator& b)
        {
            return a.m_ptr != b.m_ptr;
        };

        Iterator(const palette_id* ptr, const palette_t& palette) : m_ptr(ptr), m_palette(palette)
        {
        }

    private:
        const palette_id* m_ptr;
        const palette_t& m_palette;
    };

    [[nodiscard]] Iterator begin() const
    {
        return {buffer.begin().operator->(), palette};
    }

    [[nodiscard]] Iterator end() const
    {
        return {buffer.end().operator->(), palette};
    }

private:
    friend std::ifstream& operator>>(std::ifstream& in, Image& img);

    friend std::ostream& operator<<(std::ostream& out, const Image& img);

    [[nodiscard]] constexpr size_t pix_count() const
    {
        return width * height;
    }

    size_t width, height;
    buffer_t buffer;
    palette_t palette;
};


#endif //TDIMG_IMAGE_H

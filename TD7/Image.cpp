//
// Created by Tom on 26/10/2021.
//

#include <iostream>
#include <execution>
#include "Image.h"

std::ostream& operator<<(std::ostream& out, const Image& img)
{
    out << "P3" << std::endl;
    out << img.width << " " << img.height << " " << 255 << std::endl;
    auto pixcount = img.pix_count();
    auto ptr = &img.buffer[0];
    while (pixcount--)
        out << *ptr++ << std::endl;
    return out;
}

std::ifstream& operator>>(std::ifstream& in, Image& img)
{
    std::string header;
    in >> header;
    in.ignore();
    assert(header == "P3");
    while (in.peek() == '#')
        in.ignore(std::numeric_limits<std::streamsize>::max(), in.widen('\n'));
    int depth;
    in >> img.width >> img.height >> depth;
    assert(depth == 255);
    auto pixcount = img.pix_count();
    auto buf = std::make_unique<Pixel[]>(pixcount);
    auto ptr = &buf[0];
    while (pixcount--)
        in >> *ptr++;
    img.buffer = std::move(buf);
    return in;
}

void Image::replace_color(const Pixel&& orig, const Pixel&& subst)
{
    std::for_each(
            std::execution::par_unseq,
            &buffer[0],
            &buffer[pix_count()],
            [orig, subst](auto&& item)
            {
                if (item == orig)
                    item = subst;
            });
}

void Image::negate()
{
    std::for_each(
            std::execution::par_unseq,
            &buffer[0],
            &buffer[pix_count()],
            [](auto&& item)
            {
                item = item.negate();
            });
}

void Image::read(const std::string& filename)
{
    std::ifstream fp;
    fp.open(filename, std::ifstream::in);
    fp >> *this;
}

void Image::write(const std::string& filename) const
{
    std::ofstream fp;
    fp.open(filename, std::fstream::out);
    fp << *this;
}

void Image::threshold(uint8_t brightness)
{
    std::for_each(
            std::execution::par_unseq,
            &buffer[0],
            &buffer[pix_count()],
            [brightness](auto&& item)
            {
                item = item.brightness() < brightness
                       ? Pixel{0, 0, 0}
                       : Pixel{255, 255, 255};
            });
}

void Image::symmetry()
{
    const auto pixcount = pix_count();
    auto buf = std::make_unique<Pixel[]>(pixcount);
    std::for_each(
            std::execution::par_unseq,
            &buffer[0],
            &buffer[pixcount],
            [this, &buf, pixcount](auto&& item)
            {
                auto idx = &item - &buffer[0];
                auto res = std::div(idx, width);
                buf[pixcount - height * res.rem - res.quot - 1] = item;
            });
    std::swap(width, height);
    buffer = std::move(buf);
}

std::ifstream& operator>>(std::ifstream& in, Pixel& rgb)
{
    int r, g, b;
    in >> r >> g >> b;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Pixel& rgb)
{
    out << rgb.r + 0 << " ";
    out << rgb.g + 0 << " ";
    out << rgb.b + 0;
    return out;
}
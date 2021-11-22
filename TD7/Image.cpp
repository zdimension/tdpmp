//
// Created by Tom on 26/10/2021.
//

#include <iostream>
#include <execution>
#include <map>
#include "Image.h"

std::ostream& operator<<(std::ostream& out, const Image& img)
{
    out << "P3" << std::endl;
    out << img.width << " " << img.height << " " << 255 << std::endl;
    std::for_each(img.begin(), img.end(), [&](const Color& pixel)
    {
        out << pixel << std::endl;
    });
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
    std::vector<Color> palette{};
    std::map<Color, palette_id> palette_map{};
    std::vector<palette_id> buf(pixcount);
    auto ptr = &buf[0];
    Color col{0};
    while (pixcount--)
    {
        in >> col;
        auto it = palette_map.find(col);
        size_t id;
        if (it == std::end(palette_map))
        {
            palette.push_back(col);
            id = palette_map[col] = palette.size() - 1;
        }
        else
        {
            id = it->second;
        }
        *ptr++ = id;
    }
    img.buffer = std::move(buf);
    img.palette = std::move(palette);
    return in;
}

void Image::replace_color(const Color&& orig, const Color&& subst)
{
    for (Color& item: palette)
    {
        if (item == orig)
        {
            item = subst;
            return;
        }
    }
}

void Image::negate()
{
    std::transform(
            std::execution::par_unseq,
            std::begin(palette),
            std::end(palette),
            std::begin(palette),
            std::mem_fn(&Color::negate));
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
    std::transform(
            std::execution::par_unseq,
            std::begin(palette),
            std::end(palette),
            std::begin(palette),
            [brightness](Color item) -> Color
            {
                return item.brightness() < brightness
                       ? Color{0, 0, 0}
                       : Color{255, 255, 255};
            });
}

void Image::symmetry()
{
    std::reverse(buffer.begin(), buffer.end());
}

std::ifstream& operator>>(std::ifstream& in, Color& rgb)
{
    int r, g, b;
    in >> r >> g >> b;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Color& rgb)
{
    out << rgb.r + 0 << " ";
    out << rgb.g + 0 << " ";
    out << rgb.b + 0;
    return out;
}
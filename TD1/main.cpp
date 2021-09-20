//
// Created by Tom on 06/09/2021.
//

#include <bitset>
#include <iostream>
#include "ClampRange.hpp"

#ifdef SFML_FOUND

#include <SFML/Graphics.hpp>
#include <random>
#include <sstream>
#include <complex.h>

#endif

#define FAST

typedef unsigned int Coordinate;

std::vector<Coordinate> Clamp(Coordinate value, Coordinate boundary)
{
    return {
            (value == 0 ? boundary : value) - 1,
            value,
            (value == boundary - 1 ? 0 : value + 1)
    };
}

typedef std::pair<Coordinate, Coordinate> Position;

template<Coordinate columns, Coordinate rows, typename cell>
class GameGrid
{
public:
    typedef cell cell_t;

    typedef std::array<cell, rows * columns> grid_t;

    GameGrid() : grid()
    {
    }

    cell operator[](const Position pos) const
    {
        return grid[get_pos(pos)];
    }

    typename grid_t::reference operator[](const Position pos)
    {
        return grid[get_pos(pos)];
    }

    void next_state()
    {
        GameGrid old = *this;

        for (Coordinate y = 0; y < rows; y++)
        {
            for (Coordinate x = 0; x < columns; x++)
            {
                const Position pos = {x, y};
                (*this)[pos] = get_new_state(old, pos);
            }
        }
    }

    virtual cell get_new_state(GameGrid& old, Position pos)
    {
       return {};
    }

    virtual void fill_random()
    {
        //
    }

#if SFML_FOUND

    virtual sf::Color getColor(cell_t value) const
    {
        return {static_cast<sf::Uint8>(value != cell{} ? 255 : 0), 0, 0};
    }

    virtual cell_t getMin() const
    {
        return std::numeric_limits<cell>::min();
    }

    virtual cell_t getMax() const
    {
        return std::numeric_limits<cell>::max();
    }

#endif

    grid_t grid;

private:
    [[nodiscard]] inline Coordinate get_pos(const Position pos) const
    {
        return pos.second * columns + pos.first;
    }

protected:
    unsigned int get_neighbours(const Position pos)
    {
#ifdef FAST
        int n = 0;
        for (int y = (int) pos.second - 1; y <= (int) pos.second + 1; y++)
            for (int x = (int) pos.first - 1; x <= (int) pos.first + 1; x++)
                n += (*this)[{(x + columns) % columns, (y + rows) % rows}];
        n -= (*this)[pos];
        return n;
#else
        unsigned int neighbours = 0;

        for (auto y: Clamp(pos.second, rows))
        {
            for (auto x: Clamp(pos.first, columns))
            {
                const Position cur = {x, y};
                if (cur == pos)
                    continue;

                if ((*this)[cur])
                    neighbours++;
            }
        }

        return neighbours;
#endif
    }
};

template<Coordinate rows, Coordinate columns, typename cell>
std::ostream& operator<<(std::ostream& os, GameGrid<rows, columns, cell> const& m)
{
    for (Coordinate y = 0; y < rows; y++)
    {
        for (Coordinate x = 0; x < columns; x++)
            os << " ."[m[{x, y}]];
        os << std::endl;
    }
    return os;
}

template<Coordinate columns, Coordinate rows>
class StandardGOL : public GameGrid<columns, rows, bool>
{

public:
    bool get_new_state(GameGrid<columns, rows, bool>& old, Position pos) override
    {
        const auto isAlive = old[pos];
        const unsigned int neighbours = static_cast<StandardGOL&>(old).get_neighbours(pos);
        const bool condition = (isAlive
                                ? neighbours == 2 || neighbours == 3
                                : neighbours == 3);

        return condition;
    }

    void fill_random() override
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> d(0, 1);

        for (Coordinate n = 0; n < this->grid.size(); ++n)
        {
            this->grid[n] = d(gen);
        }
    }
};

template<Coordinate columns, Coordinate rows>
class ByteGOL : public GameGrid<columns, rows, uint8_t>
{
public:
#if SFML_FOUND

    sf::Color getColor(uint8_t value) const override
    {
        return {value, 0, 0};
    }

#endif

    void fill_random() override
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> d(0, 255);

        for (Coordinate n = 0; n < this->grid.size(); ++n)
        {
            this->grid[n] = d(gen);
        }
    }

public:
    uint8_t get_new_state(GameGrid<columns, rows, uint8_t>& old, Position pos) override
    {
        const auto isAlive = old[pos];
        const auto current = (*this)[pos];
        const unsigned int neighbours = old.get_neighbours(pos) / 255;
        const bool condition = (isAlive
                                ? neighbours == 2 || neighbours == 3
                                : neighbours == 3);
        if (condition)
        {
            for (int i = 0; i < 5 && current < 255; i++)
                current++;
        }
        else
        {
            for (int i = 0; i < 20 && current > 0; i++)
                current--;
        }
        return current;
    }
};

template<Coordinate columns, Coordinate rows>
class ComplexGOL : public GameGrid<columns, rows, std::complex<float>>
{
public:
#if SFML_FOUND

    sf::Color getColor(std::complex<float> value) const override
    {
        return HSVtoRGB(arg(value) * 180 / M_PI, 1, std::norm(value));
    }

    [[nodiscard]] std::complex<float> getMin() const override
    {
        return 0;
    }

    [[nodiscard]] std::complex<float> getMax() const override
    {
        return 1;
    }

#endif

    void fill_random() override
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> d(0, M_PI);
        std::uniform_real_distribution<double> e(0, 1);

        for (Coordinate n = 0; n < this->grid.size(); ++n)
        {
            this->grid[n] = std::polar(e(gen), d(gen));
        }
    }

public:
    std::complex<float> get_new_state(GameGrid<columns, rows, std::complex<float>>& old, Position pos) override
    {
        std::complex<float> n = 0;
        float tn = 0;
        for (int y = (int) pos.second - 1; y <= (int) pos.second + 1; y++)
            for (int x = (int) pos.first - 1; x <= (int) pos.first + 1; x++)
            {
                const auto o = old[{(x + columns) % columns, (y + rows) % rows}];
                n += o;
                tn += norm(o);
            }
        n -= old[pos];
        n /= 8;
        const double nor = norm(n);
        const auto isAlive = norm(old[pos]) > 0.01;
        const auto current = (*this)[pos];
        const bool condition = (isAlive
                                ? tn >= 2 && tn < 4
                                : tn >= 2.5 && tn < 3.5);
        if (condition)
        {
            return n;
        }
        return 0;
    }

private:
    static sf::Color HSVtoRGB(float H, float S, float V)
    {
        float C = S * V; // Chroma
        float HPrime = std::fmod(H / 60, 6.f); // H'
        float X = C * (1 - std::fabs(std::fmod(HPrime, 2.f) - 1));
        float M = V - C;

        float R = 0.f;
        float G = 0.f;
        float B = 0.f;

        switch (static_cast<int>(HPrime))
        {
            case 0:
                R = C;
                G = X;
                break; // [0, 1)
            case 1:
                R = X;
                G = C;
                break; // [1, 2)
            case 2:
                G = C;
                B = X;
                break; // [2, 3)
            case 3:
                G = X;
                B = C;
                break; // [3, 4)
            case 4:
                R = X;
                B = C;
                break; // [4, 5)
            case 5:
                R = C;
                B = X;
                break; // [5, 6)
        }

        R += M;
        G += M;
        B += M;

        sf::Color color;
        color.r = static_cast<sf::Uint8>(std::round(R * 255));
        color.g = static_cast<sf::Uint8>(std::round(G * 255));
        color.b = static_cast<sf::Uint8>(std::round(B * 255));

        return color;
    }
};

int main()
{
#ifdef SFML_FOUND
    const Coordinate columns = 320, rows = 160;
#else
    const Coordinate columns = 40, rows = 40;
#endif

    auto grid = StandardGOL<columns, rows>();
    //StandardGOL<columns, rows> grid{};

    std::array gun = {
            "                        #           ",
            "                      # #           ",
            "            ##      ##            ##",
            "           #   #    ##            ##",
            "##        #     #   ##              ",
            "##        #   # ##    # #           ",
            "          #     #       #           ",
            "           #   #                    ",
            "            ##                      ",
    };

    for(int y = 0; y < gun.size(); y++)
    {
        const char* p = gun[y];
        for (int x = 0; *p; x++, p++)
        {
            grid[{x, y}] = *p == '#';
        }
    }

#ifdef SFML_FOUND
    const int BLOCK_SIZE = 5;

    sf::RenderWindow window(sf::VideoMode(columns * BLOCK_SIZE, rows * BLOCK_SIZE), "TD1 PMP");
    sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    rectangle.setFillColor(sf::Color::Red);

    window.setFramerateLimit(60);

    sf::Image image;
    image.create(columns, rows, sf::Color(0, 0, 0));
    sf::Sprite sprite;
    sprite.scale(BLOCK_SIZE, BLOCK_SIZE);
    sf::Texture texture;

    bool running = false;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::R:
                            grid.fill_random();
                            break;
                        case sf::Keyboard::S:
                            running = !running;
                            break;
                        default:
                            grid.next_state();
                            break;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    const auto pos = sf::Mouse::getPosition(window) / BLOCK_SIZE;
                    Position gpos = {(Coordinate) pos.x, (Coordinate) pos.y};
                    grid[gpos] = grid[gpos] == grid.getMin() ? grid.getMax() : grid.getMin();
                    break;
            }
        }

        if (running)
            grid.next_state();

        window.clear();

        for (Coordinate y = 0; y < rows; y++)
        {
            for (Coordinate x = 0; x < columns; x++)
            {
                image.setPixel(x, y, grid.getColor(grid[{x, y}]));
            }
        }

        texture.loadFromImage(image);
        sprite.setTexture(texture);
        window.draw(sprite);

        window.display();

        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        std::stringstream stream;
        stream << fps;
        std::string str;
        stream >> str;
        window.setTitle(str);
    }
#else
    while (true)
    {
        std::cout << grid;
        std::cin.ignore();
        grid.next_state();
    }
#endif
}
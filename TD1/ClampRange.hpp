//
// Created by Tom on 06/09/2021.
//

#ifndef CELLULARAUTOMATA_CLAMPRANGE_HPP
#define CELLULARAUTOMATA_CLAMPRANGE_HPP

class ClampRange
{
public:
    ClampRange(unsigned int value, unsigned int boundary) : value_(value), boundary_(boundary)
    {
    }

    class iterator
            : public std::iterator<std::forward_iterator_tag, unsigned int>
    {
    public:
        explicit iterator(unsigned int value, unsigned int boundary) : value_(value), boundary_(boundary)
        {
        }

        unsigned int& operator*()
        {
            return value_;
        }

        bool operator==(const iterator& other) const
        {
            return value_ == other.value_;
        }

        bool operator!=(const iterator& other) const
        {
            return value_ != other.value_;
        }

        iterator& operator++()
        {
            if (value_ == boundary_ - 1)
                value_ = 0;
            else
                ++value_;
            return *this;
        }

        unsigned int value_;
        unsigned int boundary_;
    };

    [[nodiscard]] iterator begin() const
    {
        return iterator(value_ == 0 ? 0 : value_ - 1, boundary_);
    }

    [[nodiscard]] iterator end() const
    {
        return iterator(value_ + 2, boundary_);
    }

private:
    unsigned int value_;
    unsigned int boundary_;
};

#endif //CELLULARAUTOMATA_CLAMPRANGE_HPP

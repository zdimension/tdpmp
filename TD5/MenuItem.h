//
// Created by Tom on 25/10/2021.
//

#ifndef TD5_MENUITEM_H
#define TD5_MENUITEM_H


#include <string>
#include <memory>

class MenuItem
{
public:
    std::string text;

    virtual bool execute() = 0;

    MenuItem(std::string  text);

    virtual std::unique_ptr<MenuItem> clone() const = 0;

    virtual ~MenuItem() = default;
};


#endif //TD5_MENUITEM_H

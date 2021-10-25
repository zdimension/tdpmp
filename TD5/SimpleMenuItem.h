//
// Created by Tom on 25/10/2021.
//

#ifndef TD5_SIMPLEMENUITEM_H
#define TD5_SIMPLEMENUITEM_H


#include <memory>
#include "MenuItem.h"

class SimpleMenuItem : public MenuItem
{
public:
    SimpleMenuItem(std::string text);
    SimpleMenuItem(const SimpleMenuItem& orig);

    bool execute() override;

    std::unique_ptr<MenuItem> clone() const override;
};


#endif //TD5_SIMPLEMENUITEM_H

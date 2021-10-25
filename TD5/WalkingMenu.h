//
// Created by Tom on 25/10/2021.
//

#ifndef TD5_WALKINGMENU_H
#define TD5_WALKINGMENU_H


#include "Menu.h"
#include "MenuItem.h"

class WalkingMenu : public Menu, public MenuItem
{
public:
    WalkingMenu(const std::string& text);

    std::unique_ptr<MenuItem> clone() const override;

    bool execute() override;
};


#endif //TD5_WALKINGMENU_H

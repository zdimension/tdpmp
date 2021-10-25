//
// Created by Tom on 25/10/2021.
//

#ifndef TD5_MENU_H
#define TD5_MENU_H


#include <string>
#include <vector>
#include <memory>
#include "MenuItem.h"

class Menu
{
public:
    Menu(std::string title);

    std::string title;
    std::vector<std::unique_ptr<MenuItem>> items;

    bool activate();
    void addItem(const MenuItem& i);

    const Menu& operator=(const Menu& target) = delete;

    virtual ~Menu() = default;
};


#endif //TD5_MENU_H

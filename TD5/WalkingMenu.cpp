//
// Created by Tom on 25/10/2021.
//

#include "WalkingMenu.h"

WalkingMenu::WalkingMenu(const std::string& text) : Menu(text), MenuItem(text + " ->")
{
}

bool WalkingMenu::execute()
{
    return this->activate();
}

std::unique_ptr<MenuItem> WalkingMenu::clone() const
{
    auto res = std::make_unique<WalkingMenu>(title);
    for (const auto &item : items)
    {
        res->items.push_back(item->clone());
    }
    return res;
}

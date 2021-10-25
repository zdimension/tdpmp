//
// Created by Tom on 25/10/2021.
//

#include "SimpleMenuItem.h"
#include <iostream>

SimpleMenuItem::SimpleMenuItem(std::string text) : MenuItem(std::move(text))
{
}

bool SimpleMenuItem::execute()
{
    std::cout << "   ************** Execution de " << text << std::endl;
    return true;
}

std::unique_ptr<MenuItem> SimpleMenuItem::clone() const
{
    return std::make_unique<SimpleMenuItem>(*this);
}

SimpleMenuItem::SimpleMenuItem(const SimpleMenuItem& orig) : SimpleMenuItem(orig.text)
{

}

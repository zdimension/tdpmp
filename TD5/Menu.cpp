//
// Created by Tom on 25/10/2021.
//

#include <iostream>
#include "Menu.h"

void Menu::addItem(const MenuItem& i)
{
    items.push_back(i.clone());
}

bool Menu::activate()
{
    std::cout << title << std::endl;
    int i;
    for (i = 0; i < items.size(); i++)
    {
        std::cout << i << "- " << items.at(i)->text << std::endl;
    }
    std::cout << i << "- quitter" << std::endl;
    int selected;
    while (true)
    {
        std::cout << "Votre choix? ";
        std::cin >> selected;

        if (std::cin && selected >= 0 && selected <= items.size())
        {
            break;
        }

        std::cout << "** Invalide" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    if (selected == i)
        return false;
    items.at(selected)->execute();
    return true;
}

Menu::Menu(std::string title) : title(std::move(title))
{
}

#include <iostream>
#include "Menu.h"
#include "SimpleMenuItem.h"
#include "WalkingMenu.h"

int main()
{
    Menu main = {"LE MENU"};
    main.addItem(SimpleMenuItem{"emacs"});
    main.addItem(SimpleMenuItem{"htop"});
    WalkingMenu sub = {"COMMUNICATIONS"};
    sub.addItem(SimpleMenuItem{"pidgin"});
    sub.addItem(SimpleMenuItem{"thunderbird"});
    sub.addItem(SimpleMenuItem{"rsync my home"});
    sub.addItem(SimpleMenuItem{"traceroute"});
    main.addItem(sub);
    while (main.activate());
}

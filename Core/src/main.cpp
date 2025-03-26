/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** main.cpp
*/

#include <dlfcn.h>

#include "test.hpp"
#include "Core.hpp"

int main()
{
    std::string i = NCURSES;
    int input = -1;

    Core core;

    auto gameModuleList = core.getGameModuleList();
    auto displayModuleList = core.getDisplayModuleList();
    
    std::map<std::string, std::unique_ptr<IObject>> objects;

    test pacman ("sprite");
    objects.insert({"pacman", std::make_unique<test>(pacman)});
    displayModuleList[i]->initObject(objects);
    displayModuleList[i]->openWindow();
    while (input != 'p') {
        input = displayModuleList[i]->getInput();
        displayModuleList[i]->display(objects);
        if (input == 'c' && i == SFML) {
            displayModuleList[i]->closeWindow();
            i = NCURSES;
            displayModuleList[i]->initObject(objects);
            displayModuleList[i]->openWindow();
        }
        if (input == 'v' && i == NCURSES) {
            displayModuleList[i]->closeWindow();
            i = SFML;
            displayModuleList[i]->initObject(objects);
            displayModuleList[i]->openWindow();
        }
        if (input == 'z') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first, obj->getPosition().second - 10});
        }
        if (input == 's') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first, obj->getPosition().second + 10});
        }
        if (input == 'q') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first - 10, obj->getPosition().second});
        }
        if (input == 'd') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first + 10, obj->getPosition().second});
        }
    }
    displayModuleList[i]->closeWindow();
    return 0;
}

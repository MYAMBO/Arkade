/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** main.cpp
*/

#include <dlfcn.h>

#include "Core.hpp"

int main()
{
    std::string i = SFML;
    int input = -1;

    Core core;

    auto displayModuleList = core.getDisplayModuleList();
    auto gameModuleList = core.getGameModuleList();
    auto game = gameModuleList[NIBBLER];
    auto &objects = game->getObjects();
    displayModuleList[SFML]->initObject(objects);
    displayModuleList[SFML]->openWindow();
    while (input != 'p') {
        input = displayModuleList[i]->getInput();
        game->update(displayModuleList[i]->getMousePos(), input);
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
    }
    displayModuleList[i]->closeWindow();
    return 0;
}

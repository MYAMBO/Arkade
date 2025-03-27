/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** main.cpp
*/

#include <dlfcn.h>
#include <iostream>

#include "Core.hpp"
#include "Menu.hpp"
#include "Parsing.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Error : ./arcade <Path to Lib>" << std::endl;
        return 84;
    }
    Core core;
    Parsing parsing;

    std::filesystem::__cxx11::directory_entry file(argv[1]);
    Lib lib(file);

    auto func = lib.getIdisplayCreatorFunc();
    auto obj = func();
    auto displayModuleList = core.getDisplayModuleList();
    auto gameModuleList = core.getGameModuleList();
    parsing.setPathlib(obj->getName());
    if (parsing.ParseLib(displayModuleList) == 84) {
        std::cerr << "Error : Lib not found" << std::endl;
        return 84;
    }

    auto pathlib = parsing.getLib();    
    int input = -1;
    auto game = std::make_shared<Menu>();
    auto &objects = game->getObjects();

    displayModuleList[pathlib]->initObject(objects);
    displayModuleList[pathlib]->openWindow();
    while (input != 'p') {
        input = displayModuleList[pathlib]->getInput();
        game->update(displayModuleList[pathlib]->getMousePos(), input);
        displayModuleList[pathlib]->display(objects);
        if (input == 'c' && pathlib == SFML) {
            displayModuleList[pathlib]->closeWindow();
            pathlib = NCURSES;
            displayModuleList[pathlib]->initObject(objects);
            displayModuleList[pathlib]->openWindow();
        }
        if (input == 'v' && pathlib == NCURSES) {
            displayModuleList[pathlib]->closeWindow();
            pathlib = SFML;
            displayModuleList[pathlib]->initObject(objects);
            displayModuleList[pathlib]->openWindow();
        }
    }
    displayModuleList[pathlib]->closeWindow();
    return 0;
}
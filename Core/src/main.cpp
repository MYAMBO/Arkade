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
    std::shared_ptr<IGameModule> game = std::make_shared<Menu>(core, pathlib);
    displayModuleList[pathlib]->initObject(game->getObjects());
    displayModuleList[pathlib]->openWindow();
    while (input != 'p') {
        input = displayModuleList[pathlib]->getInput();
        game->update(displayModuleList[pathlib]->getMousePos(), input);
        displayModuleList[pathlib]->display(game->getObjects());
        if (dynamic_cast<Menu*>(game.get()) != nullptr) {
            if (game->getObjects()["4/Displays"]->getText() == SFML && pathlib != SFML) {
                displayModuleList[pathlib]->closeWindow();
                pathlib = game->getObjects()["4/Displays"]->getText();
                displayModuleList[pathlib]->initObject(game->getObjects());
                displayModuleList[pathlib]->openWindow();
                displayModuleList[pathlib]->display(game->getObjects());
            }
            if (game->getObjects()["4/Displays"]->getText() == NCURSES && pathlib != NCURSES) {
                displayModuleList[pathlib]->closeWindow();
                pathlib = game->getObjects()["4/Displays"]->getText();
                displayModuleList[pathlib]->initObject(game->getObjects());
                displayModuleList[pathlib]->openWindow();
                displayModuleList[pathlib]->display(game->getObjects());
            }
            if (std::dynamic_pointer_cast<Menu>(game)->getIsGameLaunched() == true) {
                game = gameModuleList[game->getObjects()["4/Games"]->getText()];
                displayModuleList[pathlib]->initObject(game->getObjects());
            }
        }
    }
    displayModuleList[pathlib]->closeWindow();
    return 0;
}
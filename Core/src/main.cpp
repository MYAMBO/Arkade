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
#include "Arkade.hpp"
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

    parsing.setPathlib(lib.getIdisplayCreatorFunc()()->getName());
    if (parsing.ParseLib(core.getDisplayModuleList()) == 84) {
        std::cerr << "Error : Lib not found" << std::endl;
        return 84;
    }

    Arkade arkade(parsing.getLib(), core);

    arkade.askName();
    arkade.run();
    return 0;
}
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
    if (!Core::isEnvironmentViable())
    {
        std::cerr << "Error : No graphical environment. Program stopped for security." << std::endl;
        return 84;
    }
    Core core;
    Parsing parsing;
    std::filesystem::__cxx11::directory_entry file(argv[1]);
    try
    {
        Lib lib(file);
        auto tmpLib = lib.getIdisplayCreatorFunc();
        if (tmpLib != nullptr)
            parsing.setPathlib(tmpLib()->getName());
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    if (parsing.ParseLib(core.getDisplayModuleList()) == 84) {
        std::cerr << "Error : Lib not found" << std::endl;
        return 84;
    }

    Arkade arkade(parsing.getLib(), core);

    arkade.askName();
    arkade.run();
    return 0;
}
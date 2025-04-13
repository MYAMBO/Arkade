/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** testCore.cpp
*/

#include <iostream>
#include <criterion/criterion.h>

#include "Core.hpp"

Test(Core, getDisplayModuleList)
{
    std::string lib;
    Core core;
    for (auto elt : core.getDisplayModuleList())
        lib.append(elt.first + "\n");
    std::cout << lib << std::endl;
    cr_assert_str_eq(lib.c_str(), "NCURSES\nSDL\nSFML\n");
}

Test(Core, getGameModuleList)
{
    std::string lib;
    Core core;
    for (auto elt : core.getGameModuleList())
        lib.append(elt.first + "\n");
    std::cout << lib << std::endl;
    cr_assert_str_eq(lib.c_str(), "MINESWEEPER\nSNAKE\n");
}

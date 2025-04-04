/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** testCore.cpp
*/

#include <iostream>
#include <criterion/redirect.h>
#include <criterion/criterion.h>

#include "Core.hpp"

Test(Core, getGrahicLib, .init=cr_redirect_stdout)
{
    Core core;

    for (auto elt : core.getDisplayModuleList())
        std::cout << elt.first << "\n";
    std::cout << std::fflush(stdout);
    cr_assert_stdout_eq_str("NCURSES\nSFML\n");
}

Test(Core, getGameLib, .init=cr_redirect_stdout)
{
    Core core;

    for (auto elt : core.getGameModuleList())
        std::cout << elt.first << "\n";
    std::cout << std::fflush(stdout);
    cr_assert_stdout_eq_str("MINESWEEPER\nNIBBLER\n");
}

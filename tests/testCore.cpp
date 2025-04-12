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

Test(Core, getDisplayModuleList, .init=cr_redirect_stderr)
{
    Core core;
    for (auto elt : core.getDisplayModuleList())
        std::cerr << elt.first << "\n";
    std::cerr << std::flush;
    cr_assert_stderr_eq_str("NCURSES\nSFML\n");
}

Test(Core, getGameModuleList, .init=cr_redirect_stderr)
{
    Core core;
    for (auto elt : core.getGameModuleList())
        std::cerr << elt.first << "\n";
    std::cerr << std::flush;
    cr_assert_stderr_eq_str("MINESWEEPER\nSNAKE\n");
}

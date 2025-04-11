/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Arkade
*/

#pragma once

// arcade includes
#include "Menu.hpp"


class Arkade {
    public:
        Arkade(std::string pathlib, Core core);
        ~Arkade();

        void run();
        void askName();
        void nextGame();
        void nextDisplay();
        bool exitGame(int input, bool end);
    
    private:
        Core _core;
        std::string _pathlib;
        std::shared_ptr<Menu> _menu;
        std::shared_ptr<Arcade::IGameModule> _selectedGame;
        std::shared_ptr<Arcade::IDisplayModule> _selectedDisplay;
        std::map<std::string, std::shared_ptr<Arcade::IGameModule>> _games;
        std::map<std::string, std::shared_ptr<Arcade::IDisplayModule>> _displays;
};

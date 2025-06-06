/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Arkade
*/

#pragma once

#include <vector>

#include "Menu.hpp"


class Arkade {
    public:
        Arkade(std::string pathlib, Core core);
        ~Arkade();

        void run();
        void askName();
        void nextGame();
        void nextDisplay();
        void inGameChangeDisplay();
        bool exitGame(int input, bool end);
    
    private:
        Core _core;
        std::string _pathlib;
        int _currentDisplay = 0;
        std::shared_ptr<Menu> _menu;
        std::shared_ptr<Arcade::IGameModule> _selectedGame;
        std::shared_ptr<Arcade::IDisplayModule> _selectedDisplay;
        std::map<std::string, std::shared_ptr<Arcade::IGameModule>> _games;
        std::vector<std::shared_ptr<Arcade::IDisplayModule>> _displaysVector;
        std::map<std::string, std::shared_ptr<Arcade::IDisplayModule>> _displays;
};

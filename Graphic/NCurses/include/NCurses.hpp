/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** NCurses.hpp
*/

#pragma once

#include <ncurses.h>

#include "KeyCodes.hpp"
#include "IDisplayModule.hpp"

class NCurses : public Arcade::IDisplayModule
{
    public:
        NCurses();
        ~NCurses();

        void initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>&);

        int getInput();
        std::pair<int, int> getMousePos() const;

        void openWindow();
        void closeWindow();

        void display(std::map<std::string, std::unique_ptr<Arcade::IObject>>&);

        std::string getName() const;
        short mapRGBToBasicColor(int r, int g, int b);
    private:
        std::pair<int, int> _mousePos;
        std::map<std::string, bool> _isLoad;
        std::map<std::string, int> _colorIndices;
};

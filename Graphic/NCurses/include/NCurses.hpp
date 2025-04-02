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

class NCurses : public IDisplayModule
{
    public:
        NCurses();
        ~NCurses();

        void initObject(std::map<std::string, std::unique_ptr<IObject>>&);

        int getInput();
        std::pair<int, int> getMousePos() const;

        void openWindow();
        void closeWindow();

        void display(std::map<std::string, std::unique_ptr<IObject>>&);

        std::string getName() const;
    private:
        std::pair<int, int> _mousePos;
};

extern "C"
{
    std::unique_ptr<IDisplayModule> createInstanceIDisplay()
    {
        return std::make_unique<NCurses>();
    }
}

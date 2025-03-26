/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** Minesweeper.hpp
*/

#pragma once

#include "IGameModule.hpp"

class Minesweeper : public IGameModule
{
    public:
        Minesweeper();
        ~Minesweeper();

        bool update(std::pair<int, int> mousePos, int input);

        std::map<std::string, std::unique_ptr<IObject>>& getObjects();

        std::string getName() const;

        std::size_t getScore() const;
};

extern "C" {
    std::unique_ptr<IGameModule> createInstanceIGame() {
        return std::make_unique<Minesweeper>();
    }
}

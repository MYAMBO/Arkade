/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** Minesweeper.hpp
*/

#pragma once

#include "IGameModule.hpp"

class Minesweeper : public Arcade::IGameModule {
    public:
        Minesweeper();
        ~Minesweeper();

        std::string getName() const;
        std::size_t getScore() const;
        std::map<std::string, std::unique_ptr<Arcade::IObject>>& getObjects();

        bool update(std::pair<int, int> mousePos, int input);

        void deleteObject(std::string name);
        void addObject(std::string type, std::string name);

    private:
        std::map<std::string, std::unique_ptr<Arcade::IObject>> &_objects;
};

extern "C" {
    std::unique_ptr<Arcade::IGameModule> createInstanceIGame() {
        return std::make_unique<Minesweeper>();
    }
}

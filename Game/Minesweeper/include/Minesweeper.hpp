/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** Minesweeper.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include "IGameModule.hpp"

class Minesweeper : public Arcade::IGameModule {
    public:
        Minesweeper();
        ~Minesweeper() noexcept override;

        std::string getName() const;
        std::size_t getScore() const;
        std::map<std::string, std::unique_ptr<Arcade::IObject>>& getObjects();

        bool update(std::pair<int, int> mousePos, int input);

        void deleteObject(std::string name);
        void addObject(std::string type, std::string name);

        void initGame();
        void addGridObject(std::string type, std::string name);
        void revealEmptyCells(int x, int y);
        void generateMines();
        int countAdjacentMines(int x, int y);
        int discoverCell(std::pair<int, int> mousePos);
        void flagCell(std::pair<int, int> mousePos);


    private:
        std::map<std::string, std::unique_ptr<Arcade::IObject>> _objects;
        std::map<std::string, std::vector<std::unique_ptr<Arcade::IObject>>> _gridObjects;
        
        static constexpr int GRID_WIDTH = 10;
        static constexpr int GRID_HEIGHT = 8;
        static constexpr int TILE_SIZE = 100;
        static constexpr int GRID_OFFSET_X = 400;
        static constexpr int GRID_OFFSET_Y = 100;
        int _mines = 10;
        bool _gameOver = false;
        std::vector<std::vector<bool>> _minefield;
        std::vector<std::vector<bool>> _revealed;
        std::vector<std::vector<bool>> _flagged;
};

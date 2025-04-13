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
#include <chrono>

class Minesweeper : public Arcade::IGameModule {
    public:
        Minesweeper();
        ~Minesweeper() noexcept override;

        std::string getName() const;
        std::size_t getScore() const;
        std::map<std::string, std::unique_ptr<Arcade::IObject>>& getObjects();
        
        int countAdjacentMines(int x, int y);
        int discoverCell(std::pair<int, int> mousePos);

        bool isVictory() const;
        bool update(std::pair<int, int> mousePos, int input);
        
        void initGame();
        void restartGame();
        void updateTimer();
        void generateMines(int x, int y);
        void deleteObject(std::string name);
        void revealEmptyCells(int x, int y);
        void flagCell(std::pair<int, int> mousePos);
        void addObject(std::string type, std::string name);
        void addGridObject(std::string type, std::string name);

    private:
        std::map<std::string, std::unique_ptr<Arcade::IObject>> _objects;
        std::map<std::string, std::vector<std::unique_ptr<Arcade::IObject>>> _gridObjects;
        
        static constexpr int GRID_WIDTH = 10;
        static constexpr int GRID_HEIGHT = 8;
        static constexpr int TILE_SIZE = 100;
        static constexpr int GRID_OFFSET_X = 400;
        static constexpr int GRID_OFFSET_Y = 100;
        int _mines = 10;
        int _flags = 0;
        bool _gameOver = false;
        bool _firstClick = true;
        std::vector<std::vector<bool>> _minefield;
        std::vector<std::vector<bool>> _revealed;
        std::vector<std::vector<bool>> _flagged;
        int _score;
        int _timeLimit = 180;
        bool _timeExpired = false;
        std::chrono::steady_clock::time_point _gameStartTime;
};

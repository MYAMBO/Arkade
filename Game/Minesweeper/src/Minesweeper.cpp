/*
** EPITECH PROJECT, 2024
** arkade
** File description:
** Minesweeper.cpp
*/

#include <random> 
#include "KeyCodes.hpp"
#include "MineObject.hpp"
#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
{
    initGame();
}

Minesweeper::~Minesweeper()
{
}

void Minesweeper::initGame()
{
    _minefield.clear();
    _revealed.clear();
    _flagged.clear();
    _objects.clear(); 
    _gridObjects.clear();

    _minefield.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _revealed.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _flagged.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            addGridObject(SPRITE, "grid/" + std::to_string(i) + "_" + std::to_string(j));
            _gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)][0]->setTexturePath("Minesweeper/button");
            _gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)][0]->setProperties(
                Arcade::IObject::SpriteProperties{
                    {512, 512},
                    {0, 0},
                    {3, 5},
                    {0, 0},
                    {0.2, 0.2},
                    0xDDDDDDFF
                }
            );
            _gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)][0]->setPosition(
                {GRID_OFFSET_X + i * TILE_SIZE * 1.1, GRID_OFFSET_Y + j * TILE_SIZE * 1.1}
            );
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, GRID_WIDTH - 1);
    std::uniform_int_distribution<> disY(0, GRID_HEIGHT - 1);

    int minesPlaced = 0;
    while (minesPlaced < _mines) {
        int x = disX(gen);
        int y = disY(gen);
        
        if (!_minefield[x][y]) {
            _minefield[x][y] = true;
            minesPlaced++;
        }
    }
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            _objects["grid/" + std::to_string(i) + "_" + std::to_string(j)] = 
                std::move(_gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)][0]);
        }
    }
}

void Minesweeper::generateMines()
{
    _minefield.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _revealed.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _flagged.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    int minesPlaced = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, GRID_WIDTH - 1);
    std::uniform_int_distribution<> disY(0, GRID_HEIGHT - 1);

    while (minesPlaced < _mines) {
        int x = disX(gen);
        int y = disY(gen);
        if (!_minefield[x][y]) {
            _minefield[x][y] = true;
            minesPlaced++;
        }
    }
}

void Minesweeper::addObject(std::string type, std::string name)
{
    if (_objects.find(name) == _objects.end()) {
        _objects[name] = std::make_unique<MineObject>(type, name);
    }
}

void Minesweeper::addGridObject(std::string type, std::string name)
{
    if (_gridObjects.find(name) == _gridObjects.end()) {
        _gridObjects[name].push_back(std::make_unique<MineObject>(type, name));
    }
}

int Minesweeper::discoverCell(std::pair<int, int> mousePos)
{
    int gridX = (mousePos.first - GRID_OFFSET_X) / (TILE_SIZE * 1.1);
    int gridY = (mousePos.second - GRID_OFFSET_Y) / (TILE_SIZE * 1.1);
    if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT) {
        if (_revealed[gridX][gridY] || _flagged[gridX][gridY])
            return 1;
        std::string objectName = "grid/" + std::to_string(gridX) + "_" + std::to_string(gridY);
        auto pos = _objects[objectName]->getPosition();
        auto size = std::get<Arcade::IObject::SpriteProperties>(_objects[objectName]->getProperties()).size;
        auto scale = std::get<Arcade::IObject::SpriteProperties>(_objects[objectName]->getProperties()).scale;
        if (_minefield[gridX][gridY]) {
            _gameOver = true;
            return 0;
        } else {
            _revealed[gridX][gridY] = true;
            int adjacentMines = countAdjacentMines(gridX, gridY);
            addObject(TEXT, "text_" + std::to_string(gridX) + "_" + std::to_string(gridY));
            _objects["text_" + std::to_string(gridX) + "_" + std::to_string(gridY)]->setTexturePath("Minesweeper/font");
            _objects["text_" + std::to_string(gridX) + "_" + std::to_string(gridY)]->setPosition({pos.first + (size.first * scale.first) / 4, pos.second + (size.second * scale.second) / 4});
            _objects["text_" + std::to_string(gridX) + "_" + std::to_string(gridY)]->setProperties(
                Arcade::IObject::TextProperties{0x000000, 40, std::to_string(adjacentMines)});
            _objects[objectName]->setProperties(
                Arcade::IObject::SpriteProperties{
                    {512, 512},
                    {0, 0},
                    {0, 0},
                    {0, 0},
                    {0.2, 0.2},
                    0x4c4c4c
                }
            );
            if (adjacentMines == 0)
                revealEmptyCells(gridX, gridY);
        }
    }
    return 2;
}

void Minesweeper::flagCell(std::pair<int, int> mousePos)
{
    int gridX = (mousePos.first - GRID_OFFSET_X) / (TILE_SIZE * 1.1);
    int gridY = (mousePos.second - GRID_OFFSET_Y) / (TILE_SIZE * 1.1);
    if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT) {
        if (_revealed[gridX][gridY])
            return;
        std::string objectName = "grid/" + std::to_string(gridX) + "_" + std::to_string(gridY);
        if (_flagged[gridX][gridY]) {
            _flagged[gridX][gridY] = false;
            _objects[objectName]->setProperties(
                Arcade::IObject::SpriteProperties{{512, 512}, {0, 0}, {0, 0}, {0, 0}, {0.2, 0.2}, 0xDDDDDDFF});
        } else {
            _flagged[gridX][gridY] = true;
            _objects[objectName]->setProperties(
                Arcade::IObject::SpriteProperties{{512, 512}, {0, 0}, {0, 0}, {0, 0}, {0.2, 0.2}, 0xFF0000FF});
        }
    }
}

bool Minesweeper::update(std::pair<int, int> mousePos, int input)
{
    if (_gameOver) {
        initGame();
        _gameOver = false;
    }
    if (input == K_RCLICK) {
        auto returnvalue = discoverCell(mousePos);
        if (returnvalue == 0) {
            return true;
        }
        else if (returnvalue == 1)
            return false;
    }
    else if (input == 'f')
        flagCell(mousePos);
    return false;
}

void Minesweeper::revealEmptyCells(int x, int y)
{
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
        return;
    if (_revealed[x][y] || _flagged[x][y])
        return;
    _revealed[x][y] = true;
    auto pos = _objects["grid/" + std::to_string(x) + "_" + std::to_string(y)]->getPosition();
    int adjacentMines = countAdjacentMines(x, y);
    addObject(TEXT, "text_" + std::to_string(x) + "_" + std::to_string(y));
    _objects["text_" + std::to_string(x) + "_" + std::to_string(y)]->setTexturePath("Minesweeper/font");
    _objects["text_" + std::to_string(x) + "_" + std::to_string(y)]->setPosition({pos.first, pos.second});
    _objects["text_" + std::to_string(x) + "_" + std::to_string(y)]->setProperties(
        Arcade::IObject::TextProperties{0xFFFFFF, 40, std::to_string(adjacentMines)});
    if (adjacentMines == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0)
                    continue;
                revealEmptyCells(x + i, y + j);
            }
        }
    }
}

int Minesweeper::countAdjacentMines(int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i >= 0 && x + i < GRID_WIDTH && y + j >= 0 && y + j < GRID_HEIGHT) {
                if (_minefield[x + i][y + j]) {
                    count++;
                }
            }
        }
    }
    return count;
}

void Minesweeper::deleteObject(std::string name)
{
    _objects.erase(name);
}

std::map<std::string, std::unique_ptr<Arcade::IObject>>& Minesweeper::getObjects()
{
    return _objects;
}

std::string Minesweeper::getName() const
{
    return MINESWEEPER;
}

std::size_t Minesweeper::getScore() const
{
    return 0;
}

extern "C"
{
    std::unique_ptr<Arcade::IGameModule> createInstanceIGame()
    {
        return std::make_unique<Minesweeper>();
    }
}

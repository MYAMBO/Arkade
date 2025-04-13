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
#include <iostream>

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
    _firstClick = true;

    _minefield.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _revealed.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _flagged.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _score = 0;
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
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            _objects["grid/" + std::to_string(i) + "_" + std::to_string(j)] = 
                std::move(_gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)][0]);
        }
    }
    addObject(TEXT, "4/Score");
    _objects["4/Score"]->setTexturePath("Minesweeper/font");
    _objects["4/Score"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, "Score : 0"});
    _objects["4/Score"]->setPosition({1600, 300});
    addObject(TEXT, "4/Flags");
    _objects["4/Flags"]->setTexturePath("Minesweeper/font");
    _objects["4/Flags"]->setPosition({1600, 400});
    _flags = _mines;
    std::string flagText = "Flags : " + std::to_string(_flags);
    _objects["4/Flags"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, flagText});
}

void Minesweeper::generateMines(int firstX, int firstY)
{
    _minefield.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    
    int minesPlaced = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, GRID_WIDTH - 1);
    std::uniform_int_distribution<> disY(0, GRID_HEIGHT - 1);

    while (minesPlaced < _mines) {
        int x = disX(gen);
        int y = disY(gen);
        bool isNearFirstClick = (abs(x - firstX) <= 1 && abs(y - firstY) <= 1);
        if (!_minefield[x][y] && !isNearFirstClick) {
            _minefield[x][y] = true;
            minesPlaced++;
        }
    }
    _firstClick = false;
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
        if (_firstClick)
            generateMines(gridX, gridY);
        std::string objectName = "grid/" + std::to_string(gridX) + "_" + std::to_string(gridY);
        if (_minefield[gridX][gridY]) {
            _gameOver = true;
            return 0;
        } else {
            revealEmptyCells(gridX, gridY);
        }
    }
    return 2;
}


void Minesweeper::flagCell(std::pair<int, int> mousePos)
{
    if (_flags <= 0)
        return;
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
            _flags++;
        } else {
            _flagged[gridX][gridY] = true;
            _objects[objectName]->setProperties(
                Arcade::IObject::SpriteProperties{{512, 512}, {0, 0}, {0, 0}, {0, 0}, {0.2, 0.2}, 0xFF0F00FF});
            _flags--;
        }
        std::string flagText = "Flags : " + std::to_string(_flags);
        _objects["4/Flags"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, flagText});
    }
}

void Minesweeper::restartGame()
{
    _gameOver = false;
    _firstClick = true;
    _score = 0;
    std::string scoreText = "Score : " + std::to_string(_score);
    _objects["4/Score"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, scoreText});
    _objects["4/Score"]->setPosition({1600, 300});
    _flags = _mines;
    std::string flagText = "Flags : " + std::to_string(_flags);
    _objects["4/Flags"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, flagText});
    _objects["4/Flags"]->setPosition({1600, 400});

    _minefield.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _revealed.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    _flagged.resize(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));
    
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            _revealed[i][j] = false;
            _flagged[i][j] = false;
            std::string objectName = "grid/" + std::to_string(i) + "_" + std::to_string(j);
            _objects[objectName]->setProperties(
                Arcade::IObject::SpriteProperties{{512, 512}, {0, 0}, {0, 0}, {0, 0}, {0.2, 0.2}, 0xDDDDDDFF});
        }
    }
    std::vector<std::string> objectsToDelete;
    for (auto it = _objects.begin(); it != _objects.end(); ++it) {
        std::string objectName = it->first;
        if (objectName.find("text_") == 0)
            objectsToDelete.push_back(objectName);
    }
    for (const auto& name : objectsToDelete)
        deleteObject(name);
}

bool Minesweeper::update(std::pair<int, int> mousePos, int input)
{
    if (input == 'r')
        restartGame();
    if (_gameOver) {
        initGame();
        _gameOver = false;
    }
    if (isVictory()) {
        _gameOver = true;
        return true;
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
    _score++;
    std::string scoreText = "Score : " + std::to_string(_score);
    _objects["4/Score"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, scoreText});
    _objects["4/Score"]->setPosition({1600, 300});
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
        return;
    if (_revealed[x][y] || _flagged[x][y])
        return;
    _revealed[x][y] = true;
    std::string objectName = "grid/" + std::to_string(x) + "_" + std::to_string(y);
    auto pos = _objects[objectName]->getPosition();
    auto size = std::get<Arcade::IObject::SpriteProperties>(_objects[objectName]->getProperties()).size;
    auto scale = std::get<Arcade::IObject::SpriteProperties>(_objects[objectName]->getProperties()).scale;
    _objects[objectName]->setProperties(
        Arcade::IObject::SpriteProperties{
            {512, 512},
            {0, 0},
            {0, 0},
            {0, 0},
            {0.2, 0.2},
            0x000000
        }
    );
    int adjacentMines = countAdjacentMines(x, y);
    std::string textName = "text_" + std::to_string(x) + "_" + std::to_string(y);
    addObject(TEXT, textName);
    _objects[textName]->setTexturePath("Minesweeper/font");
    _objects[textName]->setPosition({pos.first + (size.first * scale.first) / 5, pos.second + (size.second * scale.second) / 5});
    _objects[textName]->setProperties(
        Arcade::IObject::TextProperties{0x000000, 40, std::to_string(adjacentMines)}
    );
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

bool Minesweeper::isVictory() const
{
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (!_revealed[i][j] && !_minefield[i][j]) {
                return false;
            }
        }
    }
    return true;
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
    return _score;
}

extern "C"
{
    std::unique_ptr<Arcade::IGameModule> createInstanceIGame()
    {
        return std::make_unique<Minesweeper>();
    }
}

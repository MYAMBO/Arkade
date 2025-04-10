/*
** EPITECH PROJECT, 2024
** arkade
** File description:
** Minesweeper.cpp
*/

#include "MineObject.hpp"
#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
    : _objects(*(new std::map<std::string, std::unique_ptr<Arcade::IObject>>()))
{
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            addGridObject(SPRITE, "grid/" + std::to_string(i) + "_" + std::to_string(j));
            _gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)]->setTexturePath("Minesweeper/button");
            _gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)][0]->setProperties(Arcade::IObject::SpriteProperties{{TILE_SIZE, TILE_SIZE}, {0, 0}, {0, 0}, {0, 0}, {1, 1}, WHITE});
            _gridObjects["grid/" + std::to_string(i) + "_" + std::to_string(j)]->setPosition({GRID_OFFSET_X + i * TILE_SIZE, GRID_OFFSET_Y + j * TILE_SIZE});
        }
    }
    addObject(SPRITE, "2/mine");
    _objects["2/mine"]->setTexturePath("Minesweeper/bomb");
    _objects["2/mine"]->setProperties(Arcade::IObject::SpriteProperties{{1024, 1024}, {0, 0}, {3, 3}, {0, 0}, {0.1, 0.1}, WHITE});
    _objects["2/mine"]->setPosition({210, 40});
    addObject(SPRITE, "2/button");
    _objects["2/button"]->setTexturePath("Minesweeper/button");
    _objects["2/button"]->setProperties(Arcade::IObject::SpriteProperties{{512, 512}, {0, 0}, {3, 3}, {0, 0}, {0.1, 0.1}, WHITE});
    _objects["2/button"]->setPosition({235, 40});
    addObject(SPRITE, "2/flag");
    _objects["2/flag"]->setTexturePath("Minesweeper/flag");
    _objects["2/flag"]->setProperties(Arcade::IObject::SpriteProperties{{930, 899}, {0, 0}, {3, 3}, {0, 0}, {0.1, 0.1}, WHITE});
    _objects["2/flag"]->setPosition({260, 40});
    addObject(SPRITE, "1/background");
    _objects["1/background"]->setTexturePath("Minesweeper/background");
    _objects["1/background"]->setProperties(Arcade::IObject::SpriteProperties{{0, 0}, {0, 0}, {89, 31}, {0, 0}, {1, 1}, WHITE});
    _objects["1/background"]->setPosition({200, 0});
}

Minesweeper::~Minesweeper()
{
    delete &_objects;
}

bool Minesweeper::update(std::pair<int, int> mousePos, int input)
{
    // Update the objects according to the inputs
    (void)mousePos;
    (void)input;
    return true;
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

/*
** EPITECH PROJECT, 2024
** arkade
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"
#include "NibblerObject.hpp"

Nibbler::Nibbler()
    : _objects(*(new std::map<std::string, std::unique_ptr<Arcade::IObject>>()))
{
    addObject(SPRITE, "2/snakehead");
    _objects["2/snakehead"]->setTexturePath("Nibbler/nibblerHeadDown");
    _objects["2/snakehead"]->setProperties(Arcade::IObject::SpriteProperties{{100, 100}, {0, 0}, {5, 5}, {0, 0}, {1, 1}, WHITE});
    _objects["2/snakehead"]->setPosition({0, 0});
    addObject(SPRITE, "1/food");
    _objects["1/food"]->setTexturePath("Nibbler/apple");
    _objects["1/food"]->setProperties(Arcade::IObject::SpriteProperties{{100, 100}, {0, 0}, {5, 4}, {0, 0}, {1, 1}, WHITE});
    _objects["1/food"]->setPosition({100, 100});
}

Nibbler::~Nibbler()
{
    delete &_objects;
}

bool Nibbler::update(std::pair<int, int> mousePos, int input)
{
    std::pair<int, int> pos = _objects["2/snakehead"]->getPosition();
    
    _objects["2/snakehead"]->setPosition(mousePos);
    if (input == 'z') {
        _objects["2/snakehead"]->setTexturePath("Nibbler/nibblerHeadUp");
        _objects["2/snakehead"]->setPosition({pos.first, pos.second - 10});
    }
    if (input == 's') {
        _objects["2/snakehead"]->setTexturePath("Nibbler/nibblerHeadDown");
        _objects["2/snakehead"]->setPosition({pos.first, pos.second + 10});
    }
    if (input == 'q') {
        _objects["2/snakehead"]->setTexturePath("Nibbler/nibblerHeadLeft");
        _objects["2/snakehead"]->setPosition({pos.first - 10, pos.second});
    }
    if (input == 'd') {
        _objects["2/snakehead"]->setTexturePath("Nibbler/nibblerHeadRight");
        _objects["2/snakehead"]->setPosition({pos.first + 10, pos.second});
    }
    return false;
}

void Nibbler::addObject(std::string type, std::string name)
{
    if (_objects.find(name) == _objects.end()) {
        _objects[name] = std::make_unique<NibblerObject>(type, name);
    }
}

void Nibbler::deleteObject(std::string name)
{
    _objects.erase(name);
}

std::map<std::string, std::unique_ptr<Arcade::IObject>>& Nibbler::getObjects()
{
    return _objects;
}

std::string Nibbler::getName() const
{
    return NIBBLER;
}

std::size_t Nibbler::getScore() const
{
    return 0;
}

extern "C"
{
    std::unique_ptr<Arcade::IGameModule> createInstanceIGame()
    {
        return std::make_unique<Nibbler>();
    }
}

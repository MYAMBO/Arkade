/*
** EPITECH PROJECT, 2024
** arkade
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"
#include "NibblerObject.hpp"

Nibbler::Nibbler()
    : _objects(*(new std::map<std::string, std::unique_ptr<IObject>>()))
{
    addObject(SPRITE, "snakehead");
    addObject(SPRITE, "food");
    _objects["snakehead"]->setPosition({0, 0});
    _objects["food"]->setPosition({100, 100});
    _objects["snakehead"]->setTexturePath("Nibbler/nibblerHeadDown");
    _objects["food"]->setTexturePath("Nibbler/apple");
}

bool Nibbler::update(std::pair<int, int> mousePos, int input)
{
    std::pair<int, int> pos = _objects["snakehead"]->getPosition();
    
    _objects["snakehead"]->setPosition(mousePos);
    if (input == 'z') {
        _objects["snakehead"]->setTexturePath("Nibbler/nibblerHeadUp");
        _objects["snakehead"]->setPosition({pos.first, pos.second - 10});
    }
    if (input == 's') {
        _objects["snakehead"]->setTexturePath("Nibbler/nibblerHeadDown");
        _objects["snakehead"]->setPosition({pos.first, pos.second + 10});
    }
    if (input == 'q') {
        _objects["snakehead"]->setTexturePath("Nibbler/nibblerHeadLeft");
        _objects["snakehead"]->setPosition({pos.first - 10, pos.second});
    }
    if (input == 'd') {
        _objects["snakehead"]->setTexturePath("Nibbler/nibblerHeadRight");
        _objects["snakehead"]->setPosition({pos.first + 10, pos.second});
    }
    return true;
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

std::map<std::string, std::unique_ptr<IObject>>& Nibbler::getObjects()
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
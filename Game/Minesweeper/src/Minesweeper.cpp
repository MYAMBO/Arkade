/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** Minesweeper.cpp
*/

#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
    : _objects(*new std::map<std::string, std::unique_ptr<IObject>>())
{
}

Minesweeper::~Minesweeper()
{
}

std::string Minesweeper::getName() const
{
    return MINESWEEPER;
}

std::size_t Minesweeper::getScore() const
{
    return 0;
}

std::map<std::string, std::unique_ptr<IObject>>& Minesweeper::getObjects()
{
    return _objects;
}

bool Minesweeper::update(std::pair<int, int> mousePos, int input)
{
    (void)mousePos;
    (void)input;
    return false;
}

void Minesweeper::deleteObject(std::string name)
{
    _objects.erase(name);
}

void Minesweeper::addObject(std::string type, std::string name)
{
    (void)type;
    (void)name;
}

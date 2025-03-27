/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Parsing
*/

#include "Parsing.hpp"

Parsing::Parsing()
{
}

Parsing::~Parsing()
{
}

std::string Parsing::getLib() const
{
    return _pathlib;
}

int Parsing::ParseLib(std::map<std::string, std::shared_ptr<IDisplayModule>> displayModuleList)
{
    for (auto it = displayModuleList.begin(); it != displayModuleList.end(); it++) {
        if (it->first == _pathlib) {
            return 0;
        }
    }
    return 84;
}
void Parsing::setPathlib(std::string pathlib)
{
    _pathlib = pathlib;
}
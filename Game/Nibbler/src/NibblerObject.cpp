/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** NibblerObject
*/

#include "NibblerObject.hpp"

NibblerObject::NibblerObject(std::string type, std::string name)
    : _position({0, 0}), _type(type), _name(name)
{
}

NibblerObject::~NibblerObject()
{
}

void NibblerObject::setPosition(std::pair<int, int> pos)
{
    _position = pos;
}

std::pair<int, int> NibblerObject::getPosition() const
{
    return _position;
}

void NibblerObject::setSprite(std::any sprite)
{
    _sprite = sprite;
}

std::any NibblerObject::getSprite() const
{
    return _sprite;
}

void NibblerObject::setTexturePath(std::string path)
{
    _path = path;
}

std::string NibblerObject::getTexturePath()
{
    return _path;
}

std::string NibblerObject::getType() const
{
    return _type;
}

std::string NibblerObject::getName() const
{
    return _name;
}
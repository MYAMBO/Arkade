/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** MineObject
*/

#include "MineObject.hpp"

MineObject::MineObject(std::string type, std::string name)
: _position({0, 0}), _type(type), _name(name)
{
}

MineObject::~MineObject()
{
}

void MineObject::setPosition(std::pair<int, int> pos)
{
    _position = pos;
}

std::pair<int, int> MineObject::getPosition() const
{
    return _position;
}

void MineObject::setSprite(std::any sprite)
{
    _sprite = sprite;
}

void MineObject::setTexturePath(std::string path)
{
    _path = path;
}

std::string MineObject::getTexturePath()
{
    return _path;
}

std::any& MineObject::getTexture()
{
    return _texture;
}

void MineObject::setTexture(std::any texture)
{
    _texture = texture;
}

std::any& MineObject::getSprite()
{
    return _sprite;
}

std::string MineObject::getType() const
{
    return _type;
}

void MineObject::setProperties(Properties properties)
{
    _properties = properties;
}

Arcade::IObject::Properties MineObject::getProperties()
{
    return _properties;
}
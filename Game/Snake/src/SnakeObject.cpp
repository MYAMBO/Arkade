/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** SnakeObject
*/

#include "SnakeObject.hpp"

SnakeObject::SnakeObject(std::string type, std::string name)
    : _position({0, 0}), _type(type), _name(name)
{

}

SnakeObject::~SnakeObject()
{
}

void SnakeObject::setPosition(std::pair<int, int> pos)
{
    _position = pos;
}

std::pair<int, int> SnakeObject::getPosition() const
{
    return _position;
}

void SnakeObject::setSprite(std::any sprite)
{
    _sprite = sprite;
}

void SnakeObject::setTexturePath(std::string path)
{
    _path = path;
}

std::string SnakeObject::getTexturePath()
{
    return _path;
}

std::any& SnakeObject::getTexture()
{
    return _texture;
}

void SnakeObject::setTexture(std::any texture)
{
    _texture = texture;
}

std::any& SnakeObject::getSprite()
{
    return _sprite;
}

std::string SnakeObject::getType() const
{
    return _type;
}

void SnakeObject::setProperties(IObject::Properties properties)
{
    _properties = properties;
}

Arcade::IObject::Properties SnakeObject::getProperties()
{
    return _properties;
}

/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** MenuObject
*/

#include "MenuObject.hpp"

MenuObject::MenuObject(std::string type, std::string name)
    : _position({0, 0}), _type(type), _name(name)
{
}

MenuObject::~MenuObject()
{
}

void MenuObject::setPosition(std::pair<int, int> pos)
{
    _position = pos;
}

std::pair<int, int> MenuObject::getPosition() const
{
    return _position;
}

void MenuObject::setSprite(std::any sprite)
{
    _sprite = sprite;
}

void MenuObject::setTexturePath(std::string path)
{
    _path = path;
}

std::string MenuObject::getTexturePath()
{
    return _path;
}

std::any& MenuObject::getTexture()
{
    return _texture;
}

void MenuObject::setTexture(std::any texture)
{
    _texture = texture;
}

std::any& MenuObject::getSprite()
{
    return _sprite;
}

std::string MenuObject::getType() const
{
    return _type;
}

void MenuObject::setProperties(IObject::Properties properties)
{
    _properties = properties;
}

Arcade::IObject::Properties MenuObject::getProperties()
{
    return _properties;
}

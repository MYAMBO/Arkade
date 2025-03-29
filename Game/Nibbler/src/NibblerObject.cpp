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

void NibblerObject::setTexturePath(std::string path)
{
    _path = path;
}

std::string NibblerObject::getTexturePath()
{
    return _path;
}

std::any& NibblerObject::getTexture()
{
    return _texture;
}

void NibblerObject::setTexture(std::any texture)
{
    _texture = texture;
}

std::any& NibblerObject::getSprite()
{
    return _sprite;
}

std::string NibblerObject::getType() const
{
    return _type;
}

void NibblerObject::setProperties(IObject::Properties properties)
{
    _properties = properties;
}

IObject::Properties NibblerObject::getProperties()
{
    return _properties;
}

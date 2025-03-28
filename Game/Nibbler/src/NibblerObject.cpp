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

std::pair<int, int> NibblerObject::getSize() const
{
    return _size;
}

void NibblerObject::setSize(std::pair<int, int> size)
{
    _size = size;
}

std::pair<int, int> NibblerObject::getOffset() const
{
    return _offset;
}

void NibblerObject::setOffset(std::pair<int, int> offset)
{
    _offset = offset;
}

std::any& NibblerObject::getTexture()
{
    return _texture;
}

void NibblerObject::setTexture(std::any texture)
{
    _texture = texture;
}

std::string NibblerObject::getText()
{
    return _text;
}

void NibblerObject::setText(std::string text)
{
    _text = text;
}

std::any& NibblerObject::getSprite()
{
    return _sprite;
}

std::string NibblerObject::getType() const
{
    return _type;
}

std::pair<float, float>& NibblerObject::getScale()
{
    return _scale;
}

void NibblerObject::setScale(std::pair<float, float> scale)
{
    _scale = scale;
}
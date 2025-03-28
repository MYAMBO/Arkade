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

std::pair<int, int> MenuObject::getSize() const
{
    return _size;
}

void MenuObject::setSize(std::pair<int, int> size)
{
    _size = size;
}

std::pair<int, int> MenuObject::getOffset() const
{
    return _offset;
}

void MenuObject::setOffset(std::pair<int, int> offset)
{
    _offset = offset;
}

std::any& MenuObject::getTexture()
{
    return _texture;
}

void MenuObject::setTexture(std::any texture)
{
    _texture = texture;
}

std::string MenuObject::getText()
{
    return _text;
}

void MenuObject::setText(std::string text)
{
    _text = text;
}

std::any& MenuObject::getSprite()
{
    return _sprite;
}

std::string MenuObject::getType() const
{
    return _type;
}

std::pair<float, float>& MenuObject::getScale()
{
    return _scale;
}

void MenuObject::setScale(std::pair<float, float> scale)
{
    _scale = scale;
}
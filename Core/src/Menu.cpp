/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Menu
*/

#include "Menu.hpp"
#include "MenuObject.hpp"

Menu::Menu()
    : _objects(*(new std::map<std::string, std::unique_ptr<IObject>>()))
{
    addObject("sprite", "title");
    _objects["title"]->setTexturePath("arcade");   
    _objects["title"]->setOffset({1237, 316});
    _objects["title"]->setPosition({160, 90});
    _objects["title"]->setSize({1237, 316});
    addObject("sprite", "background");
    _objects["background"]->setTexturePath("background");
    _objects["background"]->setOffset({3000, 2000});
    _objects["background"]->setPosition({0, 0});
    _objects["background"]->setSize({1920, 1080});
    addObject("sprite", "arrowUp");
    _objects["arrowUp"]->setTexturePath("");
}

Menu::~Menu()
{
}

void Menu::run(std::string pathlib, Core core)
{
    (void)pathlib;
    (void)core;
}

std::map<std::string, std::unique_ptr<IObject>>& Menu::getObjects()
{
    return _objects;
}

std::string Menu::getName() const
{
    return "Menu";
}

std::size_t Menu::getScore() const
{
    return 0;
}

bool Menu::update(std::pair<int, int> mousePos, int input)
{
    (void)mousePos;
    (void)input;
    return true;
}

void Menu::addObject(std::string type, std::string name)
{
    if (_objects.find(name) == _objects.end()) {
        _objects[name] = std::make_unique<MenuObject>(type, name);
    }
}

void Menu::deleteObject(std::string name)
{
    _objects.erase(name);
}
/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Menu
*/

#include "Menu.hpp"
#include "MenuObject.hpp"

Menu::Menu(Core core)
    : _objects(*(new std::map<std::string, std::unique_ptr<IObject>>()))
{
    addObject(SPRITE, "2/title");
    _objects["2/title"]->setTexturePath("arcade");   
    _objects["2/title"]->setOffset({0, 0});
    _objects["2/title"]->setPosition({160, 90});
    _objects["2/title"]->setSize({1237, 316});
    _objects["2/title"]->setScale({1, 1});
    addObject(SPRITE, "1/background");
    _objects["1/background"]->setTexturePath("background");
    _objects["1/background"]->setOffset({0, 0});
    _objects["1/background"]->setPosition({0, 0});
    _objects["1/background"]->setSize({3000, 2000});
    _objects["1/background"]->setScale({0.64, 0.54});
    addObject(SPRITE, "2/arrowUp");
    _objects["2/arrowUp"]->setTexturePath("arrow");
    _objects["2/arrowUp"]->setOffset({1, 0});
    _objects["2/arrowUp"]->setPosition({170, 450});
    _objects["2/arrowUp"]->setSize({170, 170});
    _objects["2/arrowUp"]->setScale({0.7, 0.7});
    addObject(SPRITE, "2/arrowDown");
    _objects["2/arrowDown"]->setTexturePath("arrow");
    _objects["2/arrowDown"]->setOffset({1, 1});
    _objects["2/arrowDown"]->setPosition({170, 800});
    _objects["2/arrowDown"]->setSize({170, 170});
    _objects["2/arrowDown"]->setScale({0.7, 0.7});
    addObject(SPRITE, "2/arrowLeft");
    _objects["2/arrowLeft"]->setTexturePath("arrow");
    _objects["2/arrowLeft"]->setOffset({0, 1});
    _objects["2/arrowLeft"]->setPosition({620, 630});
    _objects["2/arrowLeft"]->setSize({170, 170});
    _objects["2/arrowLeft"]->setScale({0.7, 0.7});
    addObject(SPRITE, "2/arrowRight");
    _objects["2/arrowRight"]->setTexturePath("arrow");
    _objects["2/arrowRight"]->setOffset({2, 1});
    _objects["2/arrowRight"]->setPosition({870, 630});
    _objects["2/arrowRight"]->setSize({170, 170});
    _objects["2/arrowRight"]->setScale({0.7, 0.7});
    addObject(SPRITE, "2/play");
    _objects["2/play"]->setTexturePath("play");
    _objects["2/play"]->setOffset({0, 0});
    _objects["2/play"]->setPosition({440, 440});
    _objects["2/play"]->setSize({225, 225});
    _objects["2/play"]->setScale({1, 1});
    addObject(TEXT, "4/Games");
    _objects["4/Games"]->setTexturePath("arcade");
    _objects["4/Games"]->setText(core.getGameModuleList().begin()->second->getName());
    _objects["4/Games"]->setPosition({130, 630});
    _objects["4/Games"]->setSize({50, 50});

}

Menu::~Menu()
{
    delete &_objects;
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

bool Menu::myGetGlobalBound(std::string name, std::pair<int, int> mousePos)
{
    auto object = _objects[name].get();
    auto pos = object->getPosition();
    auto size = object->getSize();
    if (mousePos.first >= pos.first && mousePos.first <= pos.first + size.first &&
        mousePos.second >= pos.second && mousePos.second <= pos.second + size.second) {
        return true;
    }
    return false;
}

bool Menu::update(std::pair<int, int> mousePos, int input)
{
    (void)input;
    if (myGetGlobalBound("2/play", mousePos)) {
        std::cout << "Play" << std::endl;
        return true;
    }
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
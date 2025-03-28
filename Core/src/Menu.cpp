/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Menu
*/

#include "Menu.hpp"
#include "KeyCodes.hpp"
#include "MenuObject.hpp"

Menu::Menu(Core core, std::string pathlib)
    : _objects(*(new std::map<std::string, std::unique_ptr<IObject>>()))
{
    _indexGames = 0;
    _isGameLaunched = false;
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
    _objects["2/play"]->setSize({173, 173});
    _objects["2/play"]->setScale({1, 1});
    addObject(TEXT, "4/Games");
    _objects["4/Games"]->setTexturePath("arcade");
    _objects["4/Games"]->setText(core.getGameModuleList().begin()->second->getName());
    _objects["4/Games"]->setPosition({145, 670});
    _objects["4/Games"]->setSize({40, 0});
    addObject(TEXT, "4/Displays");
    _objects["4/Displays"]->setTexturePath("arcade");
    _objects["4/Displays"]->setText(pathlib);
    _objects["4/Displays"]->setPosition({720, 670});
    _objects["4/Displays"]->setSize({40, 0});
    _games = core.getGameModuleList();
    _displays = core.getDisplayModuleList();
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
    auto scale = object->getScale();
    if (scale.first != 0 && scale.second != 0)
        if ((mousePos.first >= pos.first && mousePos.first <= pos.first + size.first * scale.first) &&
            (mousePos.second >= pos.second && mousePos.second <= pos.second + size.second * scale.second)) {
            return true;
        }
    if (scale.first == 0 || scale.second == 0) {
        if (mousePos.first >= pos.first && mousePos.first <= pos.first + size.first &&
            mousePos.second >= pos.second && mousePos.second <= pos.second + size.second) {
            return true;
        }
    }
    return false;
}

bool Menu::update(std::pair<int, int> mousePos, int input)
{
    if (myGetGlobalBound("2/play", mousePos) && input == KEY_RCLICK) {
        _isGameLaunched = true;
        return true;
    }
    if (myGetGlobalBound("2/arrowUp", mousePos) && input == KEY_RCLICK) {
        _indexGames++;
        if (_indexGames >= static_cast<int>(_games.size()))
            _indexGames = 0;
        auto it = _games.begin();
        for (int i = 0; i < _indexGames; i++)
            it++;
        if (it != _games.end()) {
            _objects["4/Games"]->setText(it->second->getName());
        }
        return true;
    }
    if (myGetGlobalBound("2/arrowDown", mousePos) && input == KEY_RCLICK) {
        _indexGames--;
        if (_indexGames < 0)
            _indexGames = static_cast<int>(_games.size()) - 1;
        auto it = _games.begin();
        for (int i = 0; i < _indexGames; i++)
            it++;
        if (it != _games.end()) {
            _objects["4/Games"]->setText(it->second->getName());
        }
        return true;
    }
    if (myGetGlobalBound("2/arrowLeft", mousePos) && input == KEY_RCLICK) {
        _indexDisplays--;
        if (_indexDisplays < 0)
            _indexDisplays = static_cast<int>(_displays.size()) - 1;
        auto it = _displays.begin();
        for (int i = 0; i < _indexDisplays; i++)
            it++;
        if (it != _displays.end()) {
            _objects["4/Displays"]->setText(it->second->getName());
        }
        return true;
    }
    if (myGetGlobalBound("2/arrowRight", mousePos) && input == KEY_RCLICK) {
        _indexDisplays++;
        if (_indexDisplays >= static_cast<int>(_displays.size()))
            _indexDisplays = 0;
        auto it = _displays.begin();
        for (int i = 0; i < _indexDisplays; i++)
            it++;
        if (it != _displays.end()) {
            _objects["4/Displays"]->setText(it->second->getName());
        }
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

bool Menu::getIsGameLaunched() const
{
    return _isGameLaunched;
}
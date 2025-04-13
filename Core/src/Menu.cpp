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
    : _objects(*(new std::map<std::string, std::unique_ptr<Arcade::IObject>>()))
{
    _indexGames = 0;
    _indexDisplays = 0;
    _isGameLaunched = false;
    addObject(SPRITE, "2/title");
    _objects["2/title"]->setTexturePath("Menu/arcade");
    _objects["2/title"]->setProperties(Arcade::IObject::SpriteProperties{{1237, 316}, {0, 0}, {109, 11}, {0, 0}, {1, 1}, WHITE});
    _objects["2/title"]->setPosition({340, 90});
    addObject(SPRITE, "1/background");
    _objects["1/background"]->setTexturePath("Menu/background");
    _objects["1/background"]->setProperties(Arcade::IObject::SpriteProperties{{3000, 2000}, {0, 0}, {0, 0}, {0, 0}, {0.64, 0.54}, WHITE});
    _objects["1/background"]->setPosition({0, 0});
    addObject(SPRITE, "2/arrowUp");
    _objects["2/arrowUp"]->setTexturePath("Menu/arrow");
    _objects["2/arrowUp"]->setProperties(Arcade::IObject::SpriteProperties{{170, 170}, {170, 0}, {5, 3}, {5, 0}, {0.7, 0.7}, WHITE});
    _objects["2/arrowUp"]->setPosition({200, 450});
    addObject(SPRITE, "2/arrowDown");
    _objects["2/arrowDown"]->setTexturePath("Menu/arrow");
    _objects["2/arrowDown"]->setProperties(Arcade::IObject::SpriteProperties{{170, 170}, {170, 170}, {5, 3}, {5, 3}, {0.7, 0.7}, WHITE});
    _objects["2/arrowDown"]->setPosition({200, 800});
    addObject(SPRITE, "2/arrowLeft");
    _objects["2/arrowLeft"]->setTexturePath("Menu/arrow");
    _objects["2/arrowLeft"]->setProperties(Arcade::IObject::SpriteProperties{{170, 170}, {0, 170}, {5, 3}, {0, 3}, {0.7, 0.7}, WHITE});
    _objects["2/arrowLeft"]->setPosition({1300, 630});
    addObject(SPRITE, "2/arrowRight");
    _objects["2/arrowRight"]->setTexturePath("Menu/arrow");
    _objects["2/arrowRight"]->setProperties(Arcade::IObject::SpriteProperties{{170, 170}, {340, 170}, {5, 3}, {10, 3}, {0.7, 0.7}, WHITE});
    _objects["2/arrowRight"]->setPosition({1750, 630});
    if (!core.getGameModuleList().empty())
    {
        addObject(SPRITE, "2/play");
        _objects["2/play"]->setTexturePath("Menu/play");
        _objects["2/play"]->setProperties(Arcade::IObject::SpriteProperties{{173, 173}, {0, 0}, {27, 5}, {0, 0}, {1, 1}, WHITE});
        _objects["2/play"]->setPosition({800, 520});
    }
    addObject(TEXT, "4/Games");
    _objects["4/Games"]->setTexturePath("Menu/font");
    if (core.getGameModuleList().empty())
        _objects["4/Games"]->setProperties(Arcade::IObject::TextProperties{WHITE, 40, "No games"});
    else
        _objects["4/Games"]->setProperties(Arcade::IObject::TextProperties{WHITE, 40, core.getGameModuleList().begin()->second->getName()});
    _objects["4/Games"]->setPosition({200, 670});
    addObject(TEXT, "4/Displays");
    _objects["4/Displays"]->setTexturePath("Menu/font");
    _objects["4/Displays"]->setProperties(Arcade::IObject::TextProperties{WHITE, 40, pathlib});
    _objects["4/Displays"]->setPosition({1520, 710});
    addObject(TEXT, "4/Score");
    _objects["4/Score"]->setTexturePath("Menu/font");
    _objects["4/Score"]->setProperties(Arcade::IObject::TextProperties{WHITE, 40, "Score : 0"});
    _objects["4/Score"]->setPosition({650, 900});
    addObject(TEXT, "2/Player");
    _objects["2/Player"]->setTexturePath("Menu/font");
    _objects["2/Player"]->setProperties(Arcade::IObject::TextProperties{WHITE, 40, "Player : "});
    _objects["2/Player"]->setPosition({630, 1000});
    addObject(TEXT, "2/Name");
    _objects["2/Name"]->setTexturePath("Menu/font");
    _objects["2/Name"]->setProperties(Arcade::IObject::TextProperties{WHITE, 40, ""});
    _objects["2/Name"]->setPosition({910, 1000});
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

std::map<std::string, std::unique_ptr<Arcade::IObject>>& Menu::getObjects()
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
    try
    {
        _objects.at(name);
    }
    catch (const std::exception &e)
    {
        return false;
    }
    auto object = _objects[name].get();
    auto pos = object->getPosition();
    auto size = std::get<Arcade::IObject::SpriteProperties>(object->getProperties()).size;
    auto scale = std::get<Arcade::IObject::SpriteProperties>(object->getProperties()).scale;
    if (scale.first != 0 && scale.second != 0) {
        if ((mousePos.first >= pos.first && mousePos.first <= pos.first + size.first * scale.first) &&
            (mousePos.second >= pos.second && mousePos.second <= pos.second + size.second * scale.second)) {
            return true;
        }
    } else {
        if (mousePos.first >= pos.first && mousePos.first <= pos.first + size.first &&
            mousePos.second >= pos.second && mousePos.second <= pos.second + size.second) {
            return true;
        }
    }
    return false;
}

bool Menu::update(std::pair<int, int> mousePos, int input)
{
    if (myGetGlobalBound("2/play", mousePos) && input == K_MOUSE) {
        _isGameLaunched = true;
        return false;
    }
    if ((myGetGlobalBound("2/arrowUp", mousePos) && input == K_MOUSE) || input == K_UP) {
        _indexGames++;
        if (_indexGames >= static_cast<int>(_games.size()))
            _indexGames = 0;
        auto it = _games.begin();
        for (int i = 0; i < _indexGames; i++)
            it++;
        if (it != _games.end()) {
            auto prop = std::get<Arcade::IObject::TextProperties>(_objects["4/Games"]->getProperties());
            prop.text = it->second->getName();
            _objects["4/Games"]->setProperties(prop);
        }
        return false;
    }
    if ((myGetGlobalBound("2/arrowDown", mousePos) && input == K_MOUSE) || input == K_DOWN) {
        _indexGames--;
        if (_indexGames < 0)
            _indexGames = static_cast<int>(_games.size()) - 1;
        auto it = _games.begin();
        for (int i = 0; i < _indexGames; i++)
            it++;
        if (it != _games.end()) {
            auto prop = std::get<Arcade::IObject::TextProperties>(_objects["4/Games"]->getProperties());
            prop.text = it->second->getName();
            _objects["4/Games"]->setProperties(prop);
        }
        return false;
    }
    if ((myGetGlobalBound("2/arrowLeft", mousePos) && input == K_MOUSE) || input == K_LEFT) {
        _indexDisplays--;
        if (_indexDisplays < 0)
            _indexDisplays = static_cast<int>(_displays.size()) - 1;
        auto it = _displays.begin();
        for (int i = 0; i < _indexDisplays; i++)
            it++;
        if (it != _displays.end()) {
            auto prop = std::get<Arcade::IObject::TextProperties>(_objects["4/Displays"]->getProperties());
            prop.text = it->second->getName();
            _objects["4/Displays"]->setProperties(prop);
        }
        return false;
    }
    if ((myGetGlobalBound("2/arrowRight", mousePos) && input == K_MOUSE) || input == K_RIGHT) {
        _indexDisplays++;
        if (_indexDisplays >= static_cast<int>(_displays.size()))
            _indexDisplays = 0;
        auto it = _displays.begin();
        for (int i = 0; i < _indexDisplays; i++)
            it++;
        if (it != _displays.end()) {
            auto prop = std::get<Arcade::IObject::TextProperties>(_objects["4/Displays"]->getProperties());
            prop.text = it->second->getName();
            _objects["4/Displays"]->setProperties(prop);
        }
        return false;
    }
    return false;
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

void Menu::setIsGameLaunched(bool isGameLaunched)
{
    _isGameLaunched = isGameLaunched;
}
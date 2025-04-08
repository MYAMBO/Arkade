/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Arkade
*/

#include "Arkade.hpp"
#include "KeyCodes.hpp"

Arkade::Arkade(std::string pathlib, Core core)
    :_pathlib(pathlib)
{
    _menu = std::make_shared<Menu>(core, pathlib);
    _core = core;
}

Arkade::~Arkade()
{
}

void Arkade::run()
{
    int input = -1;

    _games = _core.getGameModuleList();
    _displays = _core.getDisplayModuleList();
    _selectedGame = std::dynamic_pointer_cast<Arcade::IGameModule>(_menu);
    _selectedDisplay = _displays[_pathlib];
    _selectedDisplay->initObject(_selectedGame->getObjects());
    _selectedDisplay->openWindow();
    while (input != 'p') {
        input = _selectedDisplay->getInput();
        _selectedGame->update(_selectedDisplay->getMousePos(), input);
        _selectedDisplay->display(_selectedGame->getObjects());
        if (_selectedGame->getName() == "Menu") {
            nextDisplay();
            nextGame();
        }
        if (exitGame(input) == false) {
            _selectedDisplay->closeWindow();
            return;
        }
    }
    _selectedDisplay->closeWindow();
}

void Arkade::nextGame()
{
    if (_menu->getIsGameLaunched() == true) {
        _selectedGame = _games[std::get<Arcade::IObject::TextProperties>(_menu->getObjects()["4/Games"]->getProperties()).text];
        _selectedDisplay->initObject(_selectedGame->getObjects());
    }
}

void Arkade::nextDisplay()
{
    if (std::get<Arcade::IObject::TextProperties>(_selectedGame->getObjects()["4/Displays"]->getProperties()).text != _pathlib) {
        _selectedDisplay->closeWindow();
        _pathlib = std::get<Arcade::IObject::TextProperties>(_selectedGame->getObjects()["4/Displays"]->getProperties()).text;
        _selectedDisplay = _displays[_pathlib];
        _selectedDisplay->initObject(_selectedGame->getObjects());
        _selectedDisplay->openWindow();
        _selectedDisplay->display(_selectedGame->getObjects());
    }
}

bool Arkade::exitGame(int input)
{
    if (input == KEY_ESC) {
        if (_selectedGame->getName() == "Menu") {
            return false;
        } else {
            _menu->setIsGameLaunched(false);
            _selectedGame = std::shared_ptr<Arcade::IGameModule>(_menu);
            _selectedDisplay->initObject(_selectedGame->getObjects());
        }
    }
    return true;
}

void Arkade::askName()
{
    std::string name;

    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    if (name.size() == 0)
        name = "Anonymous";
    _menu->getObjects()["2/Name"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, name});
    std::cout << "Welcome " << name << "!" << std::endl;
}
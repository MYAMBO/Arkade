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
    bool end;
    int input = -1;

    _games = _core.getGameModuleList();
    _displays = _core.getDisplayModuleList();
    _selectedGame = std::dynamic_pointer_cast<Arcade::IGameModule>(_menu);
    _selectedDisplay = _displays[_pathlib];
    _selectedDisplay->initObject(_selectedGame->getObjects());
    _selectedDisplay->openWindow();
    while (input != 'p') {
        input = _selectedDisplay->getInput();
        end = _selectedGame->update(_selectedDisplay->getMousePos(), input);
        if (end) {
            exitGame(input, end);
            end = false;
        }
        _selectedDisplay->display(_selectedGame->getObjects());
        if (_selectedGame->getName() == "Menu") {
            nextDisplay();
            nextGame();
        }
        if (exitGame(input, end) == false) {
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
        for (auto elt = _selectedGame->getObjects().begin(); elt != _selectedGame->getObjects().end(); elt++)
        {
            if (elt->second != nullptr)
            {
                elt->second->getTexture().reset();
                elt->second->getSprite().reset();
            }
        }
        _pathlib = std::get<Arcade::IObject::TextProperties>(_selectedGame->getObjects()["4/Displays"]->getProperties()).text;
        _selectedDisplay = _displays[_pathlib];
        _selectedDisplay->initObject(_selectedGame->getObjects());
        _selectedDisplay->openWindow();
        _selectedDisplay->display(_selectedGame->getObjects());
    }
}

bool Arkade::exitGame(int input, bool end)
{
    if (end) {
        _menu->setIsGameLaunched(false);
        auto score = _selectedGame->getScore();
        std::string scoreText = "Score: " + std::to_string(score);
        _selectedGame = std::shared_ptr<Arcade::IGameModule>(_menu);
        _selectedGame->getObjects()["4/Score"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, scoreText});
        _selectedDisplay->initObject(_selectedGame->getObjects());
        std::cout << scoreText << std::endl;
        return true;
    }
    if (input == K_ESC) {
        if (_selectedGame->getName() == "Menu") {
            return false;
        } else {
            _menu->setIsGameLaunched(false);
            auto score = _selectedGame->getScore();
            _selectedGame = std::shared_ptr<Arcade::IGameModule>(_menu);
            _selectedDisplay->initObject(_selectedGame->getObjects());
            std::string scoreText = "Score: " + std::to_string(score);
            std::cout << scoreText << std::endl;
            _selectedGame->getObjects()["4/Score"]->setProperties(Arcade::IObject::TextProperties{0xFFFFFF, 40, scoreText});
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
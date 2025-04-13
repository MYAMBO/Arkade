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

void Arkade::inGameChangeDisplay()
{
    _selectedDisplay->closeWindow();
    for (auto elt = _selectedGame->getObjects().begin(); elt != _selectedGame->getObjects().end(); elt++)
    {
        if (elt->second != nullptr)
        {
            elt->second->getTexture().reset();
            elt->second->getSprite().reset();
        }
    }
    this->_selectedDisplay = this->_displaysVector[this->_currentDisplay % this->_displaysVector.size()];
    _selectedDisplay->initObject(_selectedGame->getObjects());
    _selectedDisplay->openWindow();
}

void Arkade::run()
{
    bool end;
    int i = 0;
    int input = -1;

    _games = _core.getGameModuleList();
    _displays = _core.getDisplayModuleList();
    _selectedGame = std::dynamic_pointer_cast<Arcade::IGameModule>(_menu);
    _selectedDisplay = _displays[_pathlib];
    _selectedDisplay->initObject(_selectedGame->getObjects());
    _selectedDisplay->openWindow();
    for (auto elt : _displays) {
        this->_displaysVector.push_back(elt.second);
        if (this->_selectedDisplay == elt.second)
            this->_currentDisplay = i;
        i++;
    }
    while (true) {
        input = _selectedDisplay->getInput();
        end = _selectedGame->update(_selectedDisplay->getMousePos(), input);
        if (end) {
            exitGame(input, end);
            end = false;
        }
        _selectedDisplay->display(_selectedGame->getObjects());
        if (input == K_RIGHT && _selectedGame->getName() != "Menu") {
            this->_currentDisplay++;
            inGameChangeDisplay();
        }
        if (input == K_LEFT && _selectedGame->getName() != "Menu") {
            this->_currentDisplay--;
            inGameChangeDisplay();
        }
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
    auto text = std::get<Arcade::IObject::TextProperties>(_selectedGame->getObjects()["4/Displays"]->getProperties()).text;
    if (text != _pathlib) {
        _selectedDisplay->closeWindow();
        for (auto elt = _selectedGame->getObjects().begin(); elt != _selectedGame->getObjects().end(); elt++)
        {
            if (elt->second != nullptr)
            {
                elt->second->getTexture().reset();
                elt->second->getSprite().reset();
            }
        }
        _pathlib = text;
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
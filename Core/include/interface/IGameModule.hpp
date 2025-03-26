/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** IGame.hpp
*/

#pragma once

// std includes
#include <map>
#include <memory>
#include <string>
#include <utility>

// project includes
#include "IObject.hpp"
#include "IDisplayModule.hpp"

// Game names
#define QIX "QIX"
#define SNAKE "SNAKE"
#define PACMAN "PACMAN"
#define NIBBLER "NIBBLER"
#define SOLARFOX "SOLARFOX"
#define CENTIPEDE "CENTIPEDE"
#define MINESWEEPER "MINESWEEPER"

// Definition of the IGameModule interface
class IGameModule {
    public:
        // Default virtual destructor
        virtual ~IGameModule() = default;

        // Update the objects according to the inputs
        virtual bool update(std::pair<int, int> mousePos, int input) = 0;

        // Returns a reference to the objects' list
        virtual std::map<std::string, std::unique_ptr<IObject>>& getObjects() = 0;
        // Returns the name of the game
        virtual std::string getName() const = 0;

        // Returns the score of the player
        virtual std::size_t getScore() const = 0;
};

typedef std::unique_ptr<IGameModule> (*CreateInstanceIGame)();

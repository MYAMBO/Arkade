/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Menu
*/

#pragma once

// std includes
#include <iostream>

#include "Core.hpp"

class Menu : IGameModule {
    public:
        // Default constructor
        Menu(Core core);
        // Default destructor
        ~Menu();

        // Update the objects according to the inputs
        bool update(std::pair<int, int> mousePos, int input);

        // Returns a reference to the objects' list
        std::map<std::string, std::unique_ptr<IObject>>& getObjects();
        // Returns the name of the game
        std::string getName() const;

        // Returns the score of the player
        std::size_t getScore() const;
        void run(std::string pathlib, Core core);
        void addObject(std::string type, std::string name);
        void deleteObject(std::string name);
        bool myGetGlobalBound(std::string name, std::pair<int, int> mousePos);
    private:
        std::map<std::string, std::unique_ptr<IObject>>& _objects;
        std::map<std::string, std::unique_ptr<IGameModule>> _games;
        std::map<std::string, std::unique_ptr<IDisplayModule>> _displays;
};

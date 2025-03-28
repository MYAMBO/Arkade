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
class Menu : public IGameModule {
    public:
        Menu(Core core, std::string pathlib);
        ~Menu();
        
        bool update(std::pair<int, int> mousePos, int input);
        std::map<std::string, std::unique_ptr<IObject>>& getObjects();
        std::string getName() const;
        std::size_t getScore() const;
    
        bool getIsGameLaunched() const;
        void run(std::string pathlib, Core core);
        void addObject(std::string type, std::string name);
        void deleteObject(std::string name);
        bool myGetGlobalBound(std::string name, std::pair<int, int> mousePos);
    
    private:
        std::map<std::string, std::unique_ptr<IObject>>& _objects;
        std::map<std::string, std::shared_ptr<IGameModule>> _games;
        std::map<std::string, std::shared_ptr<IDisplayModule>> _displays;
        int _indexGames;
        int _indexDisplays;
        bool _isGameLaunched;
    };
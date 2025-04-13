/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Core.cpp
*/

#include <iostream>
#include <filesystem>

#include "Core.hpp"

Core::Core()
{
    CreateInstanceIDisplay createInstanceIDisplay;
    CreateInstanceIGame createInstanceIGame;

    for (auto file : std::filesystem::directory_iterator(LIB_PATH)) {
        if (!file.is_directory()) {
            std::cout << "path : " << file.path() << "\n";
            try
            {
                Lib lib (file);
                createInstanceIDisplay = lib.getIdisplayCreatorFunc();
                createInstanceIGame = lib.getIGameCreatorFunc();
                if (createInstanceIDisplay) {
                    std::shared_ptr<Arcade::IDisplayModule> display = createInstanceIDisplay();
                    this->_graphicList.insert({display->getName(), display});
                } else if (createInstanceIGame) {
                    std::shared_ptr<Arcade::IGameModule> game = createInstanceIGame();
                    this->_gameList.insert({game->getName(), game});
                } else
                    continue;
            }
            catch (std::exception &e)
            {
                std::cout << e.what() << "\n";
            }
        }
    }
}

Core::~Core()
{
    
}

std::map<std::string, std::shared_ptr<Arcade::IGameModule>> Core::getGameModuleList()
{
    return this->_gameList;
}

std::map<std::string, std::shared_ptr<Arcade::IDisplayModule>> Core::getDisplayModuleList()
{
    return this->_graphicList;
}

/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Core.cpp
*/

#include <filesystem>

#include "Core.hpp"

Core::Core()
{
    CreateInstanceIDisplay createInstanceIDisplay;
    CreateInstanceIGame createInstanceIGame;

    for (auto file : std::filesystem::directory_iterator(LIB_PATH)) {
        if (!file.is_directory()) {
            Lib lib (file);

            createInstanceIDisplay = lib.getIdisplayCreatorFunc();
            createInstanceIGame = lib.getIGameCreatorFunc();
            if (createInstanceIDisplay) {
                std::shared_ptr<IDisplayModule> display = createInstanceIDisplay();
                this->_graphicList.insert({display->getName(), display});
            } else if (createInstanceIGame) {
                std::shared_ptr<IGameModule> game = createInstanceIGame();
                this->_gameList.insert({game->getName(), game});
            } else
                continue;
        }
    }
}

Core::~Core()
{
    
}

std::map<std::string, std::shared_ptr<IGameModule>> Core::getGameModuleList()
{
    return this->_gameList;
}

std::map<std::string, std::shared_ptr<IDisplayModule>> Core::getDisplayModuleList()
{
    return this->_graphicList;
}

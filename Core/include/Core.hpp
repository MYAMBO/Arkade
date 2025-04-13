/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Core.hpp
*/

#pragma once

#include "Lib.hpp"

#define LIB_PATH ("lib")

class Core {
    public:
        Core();
        ~Core();

        std::map<std::string, std::shared_ptr<Arcade::IGameModule>> getGameModuleList();
        std::map<std::string, std::shared_ptr<Arcade::IDisplayModule>> getDisplayModuleList();
        static bool isEnvironmentViable();

    private:
        std::map<std::string, std::shared_ptr<Arcade::IGameModule>> _gameList;
        std::map<std::string, std::shared_ptr<Arcade::IDisplayModule>> _graphicList;
};

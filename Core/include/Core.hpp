/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Core.hpp
*/

#include "IGameModule.hpp"
#include "IDisplayModule.hpp"

class Core
{
    public:
        Core();
        ~Core();

        std::map<std::string, IGameModule *> getGameModuleList();
        std::map<std::string, IDisplayModule *> getDisplayModuleList();

    private:
        std::map<std::string, IGameModule *> _gameList;
        std::map<std::string, IDisplayModule *> _graphicList;
};

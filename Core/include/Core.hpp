/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Core.hpp
*/

#include <list>

#include "Lib.hpp"
#include "IGameModule.hpp"
#include "IDisplayModule.hpp"

#define LIB_PATH ("lib")

class Core
{
    public:
        Core();
        ~Core();

        std::map<std::string, std::shared_ptr<IGameModule>> getGameModuleList();
        std::map<std::string, std::shared_ptr<IDisplayModule>> getDisplayModuleList();

    private:
        std::map<std::string, std::shared_ptr<IGameModule>> _gameList;
        std::map<std::string, std::shared_ptr<IDisplayModule>> _graphicList;
};

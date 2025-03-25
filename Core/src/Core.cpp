/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Core.cpp
*/

#include <dlfcn.h>
#include <filesystem>

#include "Core.hpp"

Core::Core()
{
    CreateInstanceIDisplay createInstanceIDisplay;
    CreateInstanceIGame createInstanceIGame;
    std::string path = "lib";
    void* handle;

    for (auto file : std::filesystem::directory_iterator(path)) {
        if (!file.is_directory()) {
            handle = dlopen(file.path().c_str(), RTLD_LAZY);
            if (!handle)
                continue;
            createInstanceIDisplay = reinterpret_cast<CreateInstanceIDisplay>(dlsym(handle, "createInstance"));
            if (createInstanceIDisplay) {
                IDisplayModule *display = createInstanceIDisplay();
                std::cout << "add " << display->getName() << std::endl;
                this->_graphicList.insert({display->getName(), display});
            }
            createInstanceIGame = reinterpret_cast<CreateInstanceIGame>(dlsym(handle, "createInstance"));
            if (createInstanceIGame) {
                IGameModule *game = createInstanceIGame();
                this->_gameList.insert({game->getName(), game});
            }
            dlclose(handle);
        }
    }
}

Core::~Core()
{

}

std::map<std::string, IGameModule *> Core::getGameModuleList()
{
    return this->_gameList;
}

std::map<std::string, IDisplayModule *> Core::getDisplayModuleList()
{
    return this->_graphicList;
}

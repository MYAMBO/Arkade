/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Lib.hpp
*/

#include <filesystem>

#include "IGameModule.hpp"
#include "IDisplayModule.hpp"

class Lib
{
    public:
        Lib(std::filesystem::__cxx11::directory_entry file);
        ~Lib();

        CreateInstanceIGame getIGameCreatorFunc();
        CreateInstanceIDisplay getIdisplayCreatorFunc();
    private:
        void *_handle;
};

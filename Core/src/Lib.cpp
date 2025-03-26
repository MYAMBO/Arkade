/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Lib.cpp
*/

#include <dlfcn.h>

#include "Lib.hpp"

Lib::Lib(std::filesystem::__cxx11::directory_entry file)
{
    this->_handle = dlopen(file.path().c_str(), RTLD_LAZY);
}

Lib::~Lib()
{
    
}

CreateInstanceIGame Lib::getIGameCreatorFunc()
{
    return reinterpret_cast<CreateInstanceIGame>(dlsym(this->_handle, "createInstanceIGame"));
}

CreateInstanceIDisplay Lib::getIdisplayCreatorFunc()
{
    return reinterpret_cast<CreateInstanceIDisplay>(dlsym(this->_handle, "createInstanceIDisplay"));
}

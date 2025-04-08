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
    if (!this->_handle)
        printf("fail to open : %s\n", file.path().c_str());
}

Lib::~Lib()
{
    
}

CreateInstanceIGame Lib::getIGameCreatorFunc()
{
    void *tmp = dlsym(this->_handle, "createInstanceIGame");

    if (!tmp)
        printf("%s\n", dlerror());
    return reinterpret_cast<CreateInstanceIGame>(tmp);
}

CreateInstanceIDisplay Lib::getIdisplayCreatorFunc()
{
    void *tmp = dlsym(this->_handle, "createInstanceIDisplay");

    if (!tmp)
        printf("%s\n", dlerror());
    return reinterpret_cast<CreateInstanceIDisplay>(dlsym(this->_handle, "createInstanceIDisplay"));
}

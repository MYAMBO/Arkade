/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Lib.cpp
*/

#include <dlfcn.h>
#include <iostream>

#include "Lib.hpp"

Lib::Lib(std::filesystem::__cxx11::directory_entry file)
{
    this->_handle = dlopen(file.path().c_str(), RTLD_LAZY);
    if (!this->_handle)
    {
        std::cerr << "fail to open :" << file.path() << "\n";
        throw LibLoadingException();
    }
}

Lib::~Lib()
{
    dlclose(this->_handle);
}

CreateInstanceIGame Lib::getIGameCreatorFunc()
{
    void *tmp = dlsym(this->_handle, "createInstanceIGame");

    if (!tmp)
        std::cout << dlerror() << "\n";
    return reinterpret_cast<CreateInstanceIGame>(tmp);
}

CreateInstanceIDisplay Lib::getIdisplayCreatorFunc()
{
    void *tmp = dlsym(this->_handle, "createInstanceIDisplay");

    if (!tmp)
        std::cout << dlerror() << "\n";
    return reinterpret_cast<CreateInstanceIDisplay>(dlsym(this->_handle, "createInstanceIDisplay"));
}

const char* Lib::LibLoadingException::what() const noexcept
{
    return dlerror();
}

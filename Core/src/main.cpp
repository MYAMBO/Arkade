/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** main.cpp
*/

#include <dlfcn.h>

#include "test.hpp"
#include "Core.hpp"
#include "Nibbler.hpp"
#include "IDisplayModule.hpp"

IDisplayModule *changeInstance1(void *before)
{
    dlclose(before);
    void* handle = dlopen("lib/arcade_ncurses.so", RTLD_LAZY);

    if (!handle) {
        std::cerr << "Erreur de chargement: " << dlerror() << std::endl;
        return NULL;
    }

    CreateInstanceFunc createInstance = (CreateInstanceFunc)dlsym(handle, "createInstance");

    return createInstance();
}

IDisplayModule *changeInstance2(void *before)
{
    dlclose(before);
    void* handle = dlopen("lib/arcade_sfml.so", RTLD_LAZY);

    if (!handle) {
        std::cerr << "Erreur de chargement: " << dlerror() << std::endl;
        return NULL;
    }

    CreateInstanceFunc createInstance = (CreateInstanceFunc)dlsym(handle, "createInstance");

    return createInstance();
}

int main()
{
    std::string i = NCURSES;
    int input = -1;

    Core core;

    Nibbler nibbler;
    auto &objects = nibbler.getObjects();
    instance->initObject(objects);
    instance->openWindow();
    while (input != 'p') {
        input = instance->getInput();
        nibbler.update(instance->getMousePos(), IGameModule::click::NOTHING, input);
        instance->display(objects);
        if (input == 'c') {
            instance->closeWindow();
            destroyInstance(instance);
            instance = changeInstance1(handle);
            instance->initObject(objects);
            instance->openWindow();
        }
        if (input == 'v' && i == NCURSES) {
            displayModuleList[i]->closeWindow();
            i = SFML;
            displayModuleList[i]->initObject(objects);
            displayModuleList[i]->openWindow();
        }
    }
    displayModuleList[i]->closeWindow();
    return 0;
}

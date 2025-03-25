/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** main.cpp
*/

#include <dlfcn.h>

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
    int input = -1;
    void* handle = dlopen("lib/arcade_sfml.so", RTLD_LAZY);

    if (!handle) {
        std::cerr << "Erreur de chargement: " << dlerror() << std::endl;
        return 84;
    }
    
    CreateInstanceFunc createInstance = (CreateInstanceFunc)dlsym(handle, "createInstance");
    DestroyInstanceFunc destroyInstance = (DestroyInstanceFunc)dlsym(handle, "destroyInstance");
    
    if (!createInstance || !destroyInstance) {
        std::cerr << "Erreur de récupération de la lib: " << dlerror() << std::endl;
        dlclose(handle);
        return 84;
    }
    
    IDisplayModule* instance = createInstance();


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
        if (input == 'v') {
            instance->closeWindow();
            destroyInstance(instance);
            instance = changeInstance2(handle);
            instance->initObject(objects);
            instance->openWindow();
        }
    }
    instance->closeWindow();
    destroyInstance(instance);
    dlclose(handle);
    return 0;
}

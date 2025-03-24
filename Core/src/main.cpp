/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** main.cpp
*/

#include <dlfcn.h>

#include "test.hpp"
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

    std::map<std::string, std::unique_ptr<IObject>> objects;

    test pacman ("sprite");
    objects.insert({"pacman", std::make_unique<test>(pacman)});
    instance->initObject(objects);
    instance->openWindow();
    while (input != 'p') {
        input = instance->getInput();
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
        if (input == 'z') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first, obj->getPosition().second - 10});
        }
        if (input == 's') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first, obj->getPosition().second + 10});
        }
        if (input == 'q') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first - 10, obj->getPosition().second});
        }
        if (input == 'd') {
            auto obj = objects.begin()->second.get();
            obj->setPosition({obj->getPosition().first + 10, obj->getPosition().second});
        }
    }
    instance->closeWindow();
    destroyInstance(instance);
    dlclose(handle);
    return 0;
}

/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** IDisplayModule.hpp
*/

#pragma once

#include <map>
#include <memory>

#include "IObject.hpp"

class IDisplayModule
{
    public:
        enum click {
            NOTHING = 0,
            RIGHT,
            LEFT
        };
        virtual ~IDisplayModule() = default;

        virtual std::string getName() const = 0;

        virtual void initObject(std::map<std::string, std::unique_ptr<IObject>>&) = 0;

        virtual int getInput() = 0;
        virtual std::pair<int, int> getMousePos() const = 0;
        virtual click getMouseSTate() const = 0;

        virtual void openWindow() = 0;
        virtual void closeWindow() = 0;

        virtual void display(std::map<std::string, std::unique_ptr<IObject>>&) = 0;
};

typedef IDisplayModule *(*CreateInstanceIDisplay)();

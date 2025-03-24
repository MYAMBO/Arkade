/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** IObject.hpp
*/

#pragma once

#include <any>
#include <utility>
#include <iostream>

class IObject
{
    public:
        virtual ~IObject() = default;

        virtual void setPosition(std::pair<int, int>) = 0;
        virtual std::pair<int, int> getPosition() const = 0;

        virtual void setSprite(std::any) = 0;
        virtual std::any getSprite() const = 0;

        virtual void setTexturePath(std::string) = 0;
        virtual std::string getTexturePath() = 0;
        
        virtual std::string getType() const = 0;
};

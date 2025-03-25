/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** Nibbler.hpp
*/

#pragma once

#include "IGameModule.hpp"

class Nibbler : public IGameModule {
    public:
        Nibbler();
        ~Nibbler() override = default;

        bool update(std::pair<int, int>, click state, int input);

        void deleteObject(std::string name);
        void addObject(std::string type, std::string name);
        std::map<std::string, std::unique_ptr<IObject>>& getObjects() const;
    private:
        std::map<std::string, std::unique_ptr<IObject>> &_objects;
};

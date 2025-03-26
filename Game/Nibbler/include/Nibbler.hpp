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

        std::string getName() const;
        std::size_t getScore() const;
        std::map<std::string, std::unique_ptr<IObject>>& getObjects();

        bool update(std::pair<int, int> mousePos, int input);

        void deleteObject(std::string name);
        void addObject(std::string type, std::string name);

    private:
        std::map<std::string, std::unique_ptr<IObject>> &_objects;
};

extern "C" {
    std::unique_ptr<IGameModule> createInstanceIGame() {
        return std::make_unique<Nibbler>();
    }
}

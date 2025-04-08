/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** SFML.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IDisplayModule.hpp"

class SFMLModule : public Arcade::IDisplayModule
{
    public:
        SFMLModule();
        ~SFMLModule();

        std::string getName() const;

        void initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>&);

        int getInput();
        std::pair<int, int> getMousePos() const;

        void openWindow();
        void closeWindow();

        void display(std::map<std::string, std::unique_ptr<Arcade::IObject>>&);
    private:
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Event _event;
};

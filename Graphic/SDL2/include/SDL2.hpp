/*
** EPITECH PROJECT, 2025
** SDL2.hpp
** File description:
** SDL2.hpp
** created and edited by antoiix.
** All rights reserved
*/

#ifndef SDL2_HPP
#define SDL2_HPP

#include <SDL2/SDL.h>

#include "IDisplayModule.hpp"

class SDL2Module : public Arcade::IDisplayModule
{
public:
    SDL2Module();
    ~SDL2Module();

    std::string getName() const;

    void initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>&);

    int getInput();
    std::pair<int, int> getMousePos() const;

    void openWindow();
    void closeWindow();

    void display(std::map<std::string, std::unique_ptr<Arcade::IObject>>&);
private:
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> _window;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> _renderer;
    SDL_Event _event;
};

#endif //SDL2_HPP

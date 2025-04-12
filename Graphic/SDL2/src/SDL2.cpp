/*
** EPITECH PROJECT, 2025
** SDL2.cpp
** File description:
** SDL2.cpp
** created and edited by antoiix.
** All rights reserved
*/

#include "SDL2.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <KeyCodes.hpp>
#include <ostream>

SDL2Module::SDL2Module()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
}

SDL2Module::~SDL2Module()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

std::string SDL2Module::getName() const
{
    return SDL;
}

void SDL2Module::initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    // (void)objects;
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++)
    {
        type = elt->second->getType();
        path = "assets/" + elt->second->getTexturePath() + ".png";
        if (type == SPRITE)
        {
            auto texture = std::shared_ptr<SDL_Texture>(
                IMG_LoadTexture(this->_renderer.get(), path.c_str()),
                SDL_DestroyTexture);
            if (texture == nullptr)
            {
                std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
            }
            // auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());
            elt->second->setTexture(texture);
        }
    }
}


void SDL2Module::initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    this->_isLoad.clear();
    (void)objects;
}

int SDL2Module::getInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0)
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return K_ESC;
            case SDLK_UP:
                return K_UP;
            case SDLK_DOWN:
                return K_DOWN;
            case SDLK_LEFT:
                return K_LEFT;
            case SDLK_RIGHT:
                return K_RIGHT;
            default:
                return e.key.keysym.sym;
            }
        case SDL_MOUSEBUTTONDOWN:
            return K_RCLICK;
        }
    }
    return -1;
}

void SDL2Module::closeWindow()
{
    this->_isLoad.clear();
    if (_renderer)
        _renderer.reset();
    if (_window)
        _window.reset();
}

std::pair<int, int> SDL2Module::getMousePos() const
{
    int x, y;
    int width, height;

    SDL_GetWindowSize(_window.get(), &width, &height);
    SDL_GetMouseState(&x, &y);
    // std::cout << x << ", " << y << std::endl;
    return (std::pair<int, int>){1000 * x / width, 1000 * y / height};
}

void SDL2Module::openWindow()
{
    std::cout << "SDL2Module::openWindow()" << std::endl;

    // SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    //SDL_VideoInit("x11");

    this->_window.reset(SDL_CreateWindow("SDL Window",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         1920, 1080,
                                         SDL_WINDOW_SHOWN));

    this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED));

    // SDL_GL_MakeCurrent(_window.get(), SDL_GL_GetCurrentContext());
}

void SDL2Module::display(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    // std::cout << "SDL2Module::display()" << std::endl;
    std::string type;

    SDL_RenderClear(this->_renderer.get());
    for (auto elt = objects.begin(); elt != objects.end(); elt++)
    {
        type = elt->second->getType();
        if (type == SPRITE)
        {
            auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());
            // std::cout << "YANIS LE BG" << std::endl;
            auto texture = std::any_cast<std::shared_ptr<SDL_Texture>>(elt->second->getTexture());
            if (texture)
            {
                // std::cout << "HEEHEHEHE" << std::endl;
                std::pair<int, int> pos = elt->second.get()->getPosition();
                SDL_Rect srcRect = {
                    properties.offset.first, properties.offset.second, properties.size.first, properties.size.second
                };
                SDL_Rect dstRect = {
                    pos.first * 1920 / 1000, pos.second * 1080 / 1000,
                    static_cast<int>(properties.size.first * properties.scale.first),
                    static_cast<int>(properties.size.second * properties.scale.second)
                };
                SDL_RenderCopy(this->_renderer.get(), texture.get(), &srcRect, &dstRect);
            }
        }
    }
    SDL_RenderPresent(this->_renderer.get());
    // SDL_UpdateWindowSurface(this->_window.get());
}

extern "C" {
std::unique_ptr<Arcade::IDisplayModule> createInstanceIDisplay()
{
    return std::make_unique<SDL2Module>();
}
}

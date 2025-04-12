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

void SDL2Module::init(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++)
    {
        type = elt->second->getType();
        if (type == SPRITE)
        {
            if (this->_isLoad[elt->first] == true)
                continue;
            path = "assets/" + elt->second->getTexturePath() + ".png";
            SDL_Surface* surface = IMG_Load(path.c_str());
            if (surface == nullptr)
            {
                std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
            }
            elt->second->setTexture(surface);
            this->_isLoad[elt->first] = true;
        }
        if (type == TEXT)
        {
            auto properties = std::get<Arcade::IObject::TextProperties>(elt->second->getProperties());
            path = "assets/" + elt->second->getTexturePath() + ".ttf";
            TTF_Font* font = TTF_OpenFont(path.c_str(), properties.characterSize);
            if (!font)
            {
                std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
                continue;
            }

            SDL_Color color = {255, 255, 255, 255};
            SDL_Surface* surface = TTF_RenderText_Blended(font, properties.text.c_str(), color);

            SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer.get(), surface);
            if (surface == nullptr)
                std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
            else
                elt->second->setTexture(texture);

            TTF_CloseFont(font);
            this->_isLoad[elt->first] = true;
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
    return (std::pair<int, int>){1920 * x / width, 1080 * y / height};
}

void SDL2Module::openWindow()
{
    this->_window.reset(SDL_CreateWindow("SDL Window",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         1920, 1080,
                                         SDL_WINDOW_SHOWN));

    this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED));
}

void SDL2Module::display(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    int width, height;

    SDL_GetRendererOutputSize(this->_renderer.get(), &width, &height);
    init(objects);
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
